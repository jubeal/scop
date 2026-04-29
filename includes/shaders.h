#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "logs.h"
#include "parsing.h"
#include "vector.h"
#include "matrix.h"

class Shader
{
public:
  // The program ID
  unsigned int ID;

  // constructor read and builds the shader
  Shader(std::string vertexName = "default", std::string fragmentName = "default");

  // use/activate the shader
  void use();
  void deleteProgram();

  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVector4(const std::string &name, Vector4 value) const;
  void setMatrix(const std::string &name, Matrix4 value) const;

private:
  unsigned int compileShaderFromFile(std::string filePath, GLenum shaderType);
};
