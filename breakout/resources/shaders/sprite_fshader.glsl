#version 330 core

in vec2 TexCoord;

uniform sampler2D image;
uniform vec3 spriteColor;

out vec4 color;

void main()
{
  color = color = vec4(spriteColor, 1.0) * texture(image, TexCoord);
}
