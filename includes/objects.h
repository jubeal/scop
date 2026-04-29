#pragma once

#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "parsing.h"
#include "shaders.h"
#include "vector.h"
#include "matrix.h"

class Object
{
public:
  std::vector<Vector4> VERTICES;
  std::vector<unsigned int> INDICES;
  std::vector<Vector3> UVS;

  Vector4 COLOR;

  Matrix4 ROTATION;
  Matrix4 TRANSLATION;

  // OpenGL Buffers
  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;

  Object(std::string filePath, Vector4 pos);
  Object(std::vector<Vector4> vertices, std::vector<unsigned int> indices, Vector4 pos);

  void rotate(Vector3 directions, float speed, float direction = 1);
  void translate(Vector4 direction);
  void compute();
  void draw(Shader currentShader);
  void deleteBuffers();
};
