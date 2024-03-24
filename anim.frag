#version 140

uniform float time;           // used for simulation of moving lights (such as sun) and to select proper animation frame
uniform sampler2D texSampler; // sampler for texture access

smooth in vec3 position_v;    // camera space fragment position
smooth in vec2 texCoord_v;    // fragment texture coordinates

out vec4 color_f;             // outgoing fragment color

// there are 8 frames in the row, two rows total
uniform ivec2 pattern = ivec2(2, 4);
// one frame lasts 0.1s
uniform float frameDuration = 0.15f;


vec4 sampleTexture(int frame) {

  float width_offset = 1.0 / pattern.x;
  float height_offset = 1.0 / pattern.y;

  vec2 oneFrameCoord = texCoord_v / vec2(pattern);
  vec2 texCoord = oneFrameCoord - vec2((frame % pattern.x) * width_offset, (frame / pattern.x) * height_offset);

  return texture(texSampler, texCoord);
}

void main() {
  // frame of the texture to be used for explosion drawing 
  int frame = int(time / frameDuration);

  // sample proper frame of the texture to get a fragment color  
  color_f = sampleTexture(frame);
}