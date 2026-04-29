#version 330 core

flat in int vTriangleID;
out vec4 FragColor;

uniform vec4 color;

void main()
{
  float grey = 0.05 * (vTriangleID % 6);
  FragColor = vec4(grey, grey, grey, 1.0);
}