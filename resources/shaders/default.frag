#version 330 core
out vec4 FragColor;

flat in int vTriangleID;
in vec2 TexCoord;

uniform sampler2D uTexture;
uniform float textureAlpha;

void main()
{
  float grey = 0.05 * (vTriangleID % 6);
  FragColor = mix(vec4(grey, grey, grey, 1.0), texture(uTexture, TexCoord), textureAlpha);
}