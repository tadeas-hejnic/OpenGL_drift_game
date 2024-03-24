#version 140

uniform float time;           // used for simulation of moving lights (such as sun) and to select proper animation frame
uniform sampler2D texSampler; // sampler for texture access

smooth in vec3 position_v;    // camera space fragment position
smooth in vec2 texCoord_v;    // fragment texture coordinates

out vec4 color_f;             // outgoing fragment color

uniform ivec2 pattern = ivec2(1, 2);


vec4 sampleTexture(float time, int state) {

  float height_offset = 1.0 / pattern.y;

  vec2 oneFrameCoord = texCoord_v / vec2(pattern);
  
  vec2 texCoord = oneFrameCoord;

  if (state == 1)
	texCoord = oneFrameCoord + vec2(0.0, (time / pattern.x) * height_offset);
  else if (state == 2)
	texCoord = oneFrameCoord + vec2(0.0, height_offset);
  else if (state == 3)
	texCoord = oneFrameCoord + vec2(0.0, 0.5 + (time / pattern.x) * height_offset);
	
  return texture(texSampler, texCoord);
}

void main() {
  // sample proper frame of the texture to get a fragment color
  int state = int(time) % 4;

  color_f = sampleTexture(time - int(time), state);
}