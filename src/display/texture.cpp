#include "texture.h"

Texture::Texture(std::string filePath, bool flipY)
{
  ParsedBMPDatas bmpTexture = parseBmpFile(filePath, flipY);

  glGenTextures(1, &ID);
  glBindTexture(GL_TEXTURE_2D, ID);

  // Set texture wrapping/filtering options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // Generate texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bmpTexture.width, bmpTexture.height, 0,
               GL_RGB, GL_UNSIGNED_BYTE, bmpTexture.pixels.data());
  glGenerateMipmap(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::use(GLenum activeTexture)
{
  glActiveTexture(activeTexture);
  glBindTexture(GL_TEXTURE_2D, ID);
  glActiveTexture(GL_TEXTURE0);
}

void Texture::deleteTexture()
{
  glDeleteTextures(1, &ID);
}