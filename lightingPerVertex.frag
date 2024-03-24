#version 140

struct Material {           // structure that describes currently used material
  vec3  ambient;            // ambient component
  vec3  diffuse;            // diffuse component
  vec3  specular;           // specular component
  float shininess;          // sharpness of specular reflection

  bool  useTexture;         // defines whether the texture is used or not
};

uniform sampler2D texSampler;  // sampler for the texture access
// uniform sampler2D texSampler2;  // sampler for the texture access

uniform Material material;     // current material

uniform bool useFog;
uniform vec3 carPosition;

in vec3 interpolatedPosition;
// in vec3 vPosition;
smooth in vec4 color_v;        // incoming fragment color (includes lighting)
smooth in vec2 texCoord_v;     // fragment texture coordinates
// smooth in vec2 texCoord_v2;     // fragment texture coordinates
out vec4       color_f;        // outgoing fragment color

void main() {

    color_f = color_v;

    // if material has a texture -> apply it
    if(material.useTexture)
        color_f = color_v * texture(texSampler, texCoord_v);

    if (useFog) {

        float dist = length(interpolatedPosition);
        // float dist = length(vPosition - carPosition);
        float fog_blending_factor = exp(-1 * dist);
        color_f = fog_blending_factor * color_f + (1 - fog_blending_factor) * vec4(0.6);
    }
}
