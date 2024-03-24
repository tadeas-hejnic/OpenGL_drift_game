
#version 140

// IMPORTANT: !!! lighting is evaluated in camera space !!!

struct Material {      // structure that describes currently used material
    vec3  ambient;       // ambient component
    vec3  diffuse;       // diffuse component
    vec3  specular;      // specular component
    float shininess;     // sharpness of specular reflection

    bool  useTexture;    // defines whether the texture is used or not
};

// warning: sampler inside the Material struct can cause problems -> so its outside
uniform sampler2D texSampler;  // sampler for the texture access

struct Light {         // structure describing light parameters
    vec3  ambient;       // intensity & color of the ambient component
    vec3  diffuse;       // intensity & color of the diffuse component
    vec3  specular;      // intensity & color of the specular component
    vec3  position;      // light position
    vec3  spotDirection; // spotlight direction
    float spotCosCutOff; // cosine of the spotlight's half angle
    float spotExponent;  // distribution of the light energy within the reflector's cone (center->cone's edge)
    float intensity;
};

in vec3 position;           // vertex position in world space
in vec3 normal;             // vertex normal
in vec2 texCoord;           // incoming texture coordinates

uniform float time;         // time used for simulation of moving lights (such as sun)
uniform Material material;  // current material

uniform mat4 PVMmatrix;     // Projection * View * Model  --> model to clip coordinates
uniform mat4 Vmatrix;       // View                       --> world to eye coordinates
uniform mat4 Mmatrix;       // Model                      --> model to world coordinates
uniform mat4 normalMatrix;  // inverse transposed Mmatrix

uniform vec3 reflectorPosition;   // reflector position (world coordinates)
uniform vec3 reflectorDirection;  // reflector direction (world coordinates)

// -----------------------------------------
uniform vec3 lampPositionLine1;   // lamp position (world coordinates)
uniform int numOfLine1;
uniform float distanceLine;
uniform float lampIntensity;
uniform float sunIntensity;
// -----------------------------------------
uniform vec3 pointLightPosition = vec3(-0.7, 0.0, 0.1);


out vec3 interpolatedPosition;
// out vec3 vPosition;
smooth out vec2 texCoord_v;  // outgoing texture coordinates
// smooth out vec2 texCoord_v2;  // outgoing texture coordinates
smooth out vec4 color_v;     // outgoing fragment color

vec4 pointLight(Light light, Material material, vec3 vertexPosition, vec3 vertexNormal) {
    vec3 posToLight = vertexPosition - light.position;
	float dist = length(posToLight);
	posToLight = normalize(posToLight);
	
	float diffuse = max(0.0, dot(vertexNormal, -posToLight));

	float total = 1.0 + 2.0*dist + 10.0*dist*dist;

	return vec4(vec3(1.0, 0.2, 0.0)*(light.ambient+diffuse)/total, 1.0);
}


vec4 spotLight(Light light, Material material, vec3 vertexPosition, vec3 vertexNormal) {

    vec3 ret = vec3(0.0);

    vec3 L = normalize(light.position - vertexPosition);
    vec3 R = reflect(-1 * L, vertexNormal);
    vec3 V = normalize(vec3(0.0f) - vertexPosition); // vec3(0.0f) = cameraPosition

    // ambient_reflected = ambient_light * ambient_material
    vec3 ambient_reflected = light.ambient * material.ambient;

    // diffuse_reflected = max(cos(alpha), 0) * diffuse_light * diffuse_material |-> cos(alpha) = L*N
    vec3 diffuse_reflected = max(dot(L, vertexNormal), 0.0f) * light.diffuse * material.diffuse;


    // specular_reflected = (max(cos(alpha), 0))^shininess_material * specular_light * specular_material |-> cos(alpha) = R*V 
    vec3 specular_reflected = pow(max(dot(R, V), 0.0f), material.shininess) * light.specular * material.specular;

    // light = spotlightEffect * (ambient_reflected + diffuse_reflected + specular_reflected)
    ret = ambient_reflected + diffuse_reflected + specular_reflected;

    float cos_angle = max(dot(light.spotDirection, -1 * L), 0.0f);

    if (cos_angle >= light.spotCosCutOff)
        return vec4(ret * pow(cos_angle, light.spotExponent), 1.0) * light.intensity;;

    // outside of the cone -> no light
    return vec4(vec3(0.0f), 1.0);
}


vec4 directionalLight(Light light, Material material, vec3 vertexPosition, vec3 vertexNormal) {

    vec3 ret = vec3(0.0);

    vec3 L = normalize(light.position);
    vec3 R = reflect(-1 * L, vertexNormal);
    vec3 V = normalize(vec3(0.0f) - vertexPosition); // vec3(0.0f) = cameraPosition

    // ambient_reflected = ambient_light * ambient_material
    vec3 ambient_reflected = light.ambient * material.ambient;

    // diffuse_reflected = max(cos(alpha), 0) * diffuse_light * diffuse_material |-> cos(alpha) = L*N
    vec3 diffuse_reflected = max(dot(L, vertexNormal), 0.0f) * light.diffuse * material.diffuse;

    // specular_reflected = (max(cos(alpha), 0))^shininess_material * specular_light * specular_material |-> cos(alpha) = R*V 
    vec3 specular_reflected = pow(max(dot(R, V), 0.0f), material.shininess) * light.specular * material.specular;

    // light = spotlightEffect * (ambient_reflected + diffuse_reflected + specular_reflected)
    ret = ambient_reflected + diffuse_reflected + specular_reflected;
    ret *= sunIntensity;

    return vec4(ret, 1.0);
}

// hardcoded lights
Light sun;
float sunSpeed = 0.5f;
Light carReflector;
Light lampReflector;
Light pointLightReflector;

void setupLights() {

    // set up sun parameters
    sun.ambient = vec3(0.0);
    sun.diffuse = vec3(1.0, 1.0, 0.5f);
    sun.specular = vec3(1.0);

    sun.position = vec3(0.0, 1.0, 1.0);

      // set up car reflector parameters
    carReflector.ambient = vec3(0.2f);
    carReflector.diffuse = vec3(1.0);
    carReflector.specular = vec3(1.0);
    carReflector.spotCosCutOff = 0.95f;
    carReflector.spotExponent = 8.0;
    carReflector.intensity = 1.0f;


    // set properly reflector direction and position taking into account reflectorPosition
    // and reflectorDirection uniforms
    carReflector.position = (Vmatrix * vec4(reflectorPosition, 1.0)).xyz;
    carReflector.spotDirection = normalize((Vmatrix * vec4(reflectorDirection, 0.0)).xyz);


    lampReflector.ambient = vec3(0.2f);
    lampReflector.diffuse = vec3(1.0);
    lampReflector.specular = vec3(1.0);
    lampReflector.spotCosCutOff = 0.96f;
    lampReflector.spotExponent = 10.0;
    lampReflector.intensity = lampIntensity;


    pointLightReflector.ambient = vec3(0.2f);
    pointLightReflector.diffuse = vec3(1.0);
    pointLightReflector.specular = vec3(1.0);
    pointLightReflector.spotCosCutOff = 0.96f;
    pointLightReflector.spotExponent = 10.0;
    pointLightReflector.intensity = 1.0;
}

void main() {

    setupLights();

    // eye-coordinates position and normal of vertex
    vec3 vertexPosition = (Vmatrix * Mmatrix * vec4(position, 1.0)).xyz;         // vertex in eye coordinates
    vec3 vertexNormal = normalize((Vmatrix * normalMatrix * vec4(normal, 0.0)).xyz);   // normal in eye coordinates by NormalMatrix

    // initialize the output color with the global ambient term
    vec3 globalAmbientLight = vec3(0.4f);
    vec4 outputColor = vec4(material.ambient * globalAmbientLight, 0.0);

    // accumulate contributions from all lights
    outputColor += directionalLight(sun, material, vertexPosition, vertexNormal);
    outputColor += spotLight(carReflector, material, vertexPosition, vertexNormal);

    for (int i = 0; i < numOfLine1; i++) {
        lampReflector.position = (Vmatrix * vec4(lampPositionLine1 + vec3(i*distanceLine, 0.0, 0.4), 1.0)).xyz;
        lampReflector.spotDirection = normalize((Vmatrix * vec4(0.0, 0.15, -1.0, 0.0)).xyz);
        outputColor += spotLight(lampReflector, material, vertexPosition, vertexNormal);
    }

    for (int i = 0; i < numOfLine1; i++) {
        lampReflector.position = (Vmatrix * vec4(lampPositionLine1 + vec3(i * distanceLine, -0.4, 0.4), 1.0)).xyz;
        lampReflector.spotDirection = normalize((Vmatrix * vec4(0.0, -0.15, -1.0, 0.0)).xyz);
        outputColor += spotLight(lampReflector, material, vertexPosition, vertexNormal);
    }

    for (int i = 0; i < numOfLine1; i++) {
        lampReflector.position = (Vmatrix * vec4(lampPositionLine1 + vec3(i * distanceLine, 0.37, 0.4), 1.0)).xyz;
        lampReflector.spotDirection = normalize((Vmatrix * vec4(0.0, -0.15, -1.0, 0.0)).xyz);
        outputColor += spotLight(lampReflector, material, vertexPosition, vertexNormal);
    }

    for (int i = 0; i < numOfLine1; i++) {
        lampReflector.position = (Vmatrix * vec4(lampPositionLine1 + vec3(i * distanceLine, -0.66, 0.4), 1.0)).xyz;
        lampReflector.spotDirection = normalize((Vmatrix * vec4(0.0, 0.15, -1.0, 0.0)).xyz);
        outputColor += spotLight(lampReflector, material, vertexPosition, vertexNormal);
    }

    for (int i = 0; i < numOfLine1; i++) {
        lampReflector.position = (Vmatrix * vec4(
            vec3(lampPositionLine1.x, 1.7, lampPositionLine1.z)
            + vec3(i * distanceLine, 0.0, 0.4), 1.0)).xyz;
        lampReflector.spotDirection = normalize((Vmatrix * vec4(0.0, 0.15, -1.0, 0.0)).xyz);
        outputColor += spotLight(lampReflector, material, vertexPosition, vertexNormal);
    }
    for (int i = 0; i < numOfLine1; i++) {
        lampReflector.position = (Vmatrix * vec4(
            vec3(lampPositionLine1.x, -1.7, lampPositionLine1.z)
            + vec3(i * distanceLine, 0.0, 0.4), 1.0)).xyz;
        lampReflector.spotDirection = normalize((Vmatrix * vec4(0.0, -0.15, -1.0, 0.0)).xyz);
        outputColor += spotLight(lampReflector, material, vertexPosition, vertexNormal);
    }

    lampReflector.position = (Vmatrix * vec4(vec3(-0.92, -1.7, lampPositionLine1.z + 0.4), 1.0)).xyz;
    lampReflector.spotDirection = normalize((Vmatrix * vec4(0.0, -0.15, -1.0, 0.0)).xyz);
    outputColor += spotLight(lampReflector, material, vertexPosition, vertexNormal);

    lampReflector.position = (Vmatrix * vec4(vec3(-0.92, 1.7, lampPositionLine1.z + 0.4), 1.0)).xyz;
    lampReflector.spotDirection = normalize((Vmatrix * vec4(0.0, 0.15, -1.0, 0.0)).xyz);
    outputColor += spotLight(lampReflector, material, vertexPosition, vertexNormal);

    pointLightReflector.position = (Vmatrix * vec4(pointLightPosition, 1.0)).xyz;
    outputColor += pointLight(pointLightReflector, material, vertexPosition, vertexNormal);

    // vertex position after the projection (gl_Position is built-in output variable)
    gl_Position = PVMmatrix * vec4(position, 1);   // out:v vertex in clip coordinates

    interpolatedPosition = (Vmatrix * Mmatrix * vec4(vertexPosition, 1.0)).xyz;
    // vPosition = vertexPosition;
    // outputs entering the fragment shader
    color_v = outputColor;
    texCoord_v = texCoord;
    // texCoord_v2 = texCoord;
}
