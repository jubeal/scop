#include "shaders.h"

Shader::Shader(std::string vertexName, std::string fragmentName)
{
  std::string defaultVertexShaderFilePath = "./resources/shaders/" + vertexName + ".vert";
  std::string defaultFragmentShaderFilePath = "./resources/shaders/" + fragmentName + ".frag";

  try
  {
    unsigned int vertexShaderId = compileShaderFromFile(defaultVertexShaderFilePath, GL_VERTEX_SHADER);
    unsigned int fragmentShaderId = compileShaderFromFile(defaultFragmentShaderFilePath, GL_FRAGMENT_SHADER);
    int success;
    char infoLog[512];

    ID = glCreateProgram();

    glAttachShader(ID, vertexShaderId);
    glAttachShader(ID, fragmentShaderId);
    glLinkProgram(ID);

    // Chech if link was successful
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if (!success)
    {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n"
                << infoLog << std::endl;
      throw -300;
    }

    // Linked shaders can be deleted
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
  }
  catch (int error)
  {
    logError("ERROR::SHADER::CREATION:", vertexName + ' ' + fragmentName);
    if (error != -300)
      throw error;
    throw -300;
  }
};

void Shader::use()
{
  glUseProgram(ID);
}

void Shader::deleteProgram()
{
  glDeleteProgram(ID);
}

unsigned int Shader::compileShaderFromFile(std::string filePath, GLenum shaderType)
{
  unsigned int shaderId;
  std::string shaderSource = readFileToString(filePath);
  const char *sourceStringified = shaderSource.c_str();
  int success;
  char infoLog[512];

  shaderId = glCreateShader(shaderType);
  glShaderSource(shaderId, 1, &sourceStringified, NULL);
  glCompileShader(shaderId);

  // Check if commpilation was successful
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
    logError("ERROR::SHADER::COMPILATION_FAILED", filePath + "\n" + infoLog);
    throw -300;
  }

  return shaderId;
}

void Shader::setBool(const std::string &name, bool value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
  glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
  glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVector4(const std::string &name, Vector4 value) const
{
  glUniform4f(glGetUniformLocation(ID, name.c_str()), value.X, value.Y, value.Z, value.W);
}

void Shader::setMatrix(const std::string &name, Matrix4 value) const
{
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.M.data()->data());
}
