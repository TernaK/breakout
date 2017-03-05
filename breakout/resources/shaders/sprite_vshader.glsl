#version 330 core

layout (location = 0) in vec4 spriteData;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main() {
  gl_Position = projection * model * vec4(spriteData.xy, 0.0, 1.0);
  TexCoord = spriteData.zw;
}