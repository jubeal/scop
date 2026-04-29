#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

#include "parsing.h"

class Texture
{
public:
  unsigned int ID;

  Texture(std::string filePath, bool flipY = false);

  void use(GLenum activeTexture = GL_TEXTURE0);
  void deleteTexture();
};