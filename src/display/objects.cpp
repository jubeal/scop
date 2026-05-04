#include "objects.h"

Object::Object(std::string filePath, Vector4 pos)
{
  ObjectFileDatas obj = readObjectFile(filePath);

  VERTICES = obj.vertices;
  INDICES = obj.indices;
  TRANSLATION = Matrix4::translation(pos);
  int nbVertices = VERTICES.size();
  for(int i = 0; i < nbVertices; i++)
  {
    int modulo = i % 6;
    Vector3 uv(0, 0, 0);
    switch(modulo)
    {
      case 1:
        uv = {1, 0, 0};
        break;
      case 2:
        uv = {1, 1, 0};
        break;
      case 4:
        uv = {1, 1, 0};
        break;
      case 5:
        uv = {0, 1, 0};
        break;
    }
    UVS.push_back(uv);
  }

  ROTATION = Matrix4::identity();

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
}

Object::Object(std::vector<Vector4> vertices, std::vector<unsigned int> indices, Vector4 pos)
{
  VERTICES = vertices;
  INDICES = indices;
  TRANSLATION = Matrix4::translation(pos);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
}

void Object::rotate(Vector3 directions, float speed, float direction)
{
  ROTATION = ROTATION * Matrix4::rotationX(directions.X * speed * direction);
  ROTATION = ROTATION * Matrix4::rotationY(directions.Y * speed * direction);
  ROTATION = ROTATION * Matrix4::rotationZ(directions.Z * speed * direction);
}

void Object::translate(Vector4 direction)
{
  TRANSLATION = TRANSLATION * Matrix4::translation(direction);
}

void Object::compute()
{
  std::vector<float> glVertices;
  int nbVertices = VERTICES.size();

  for (int i = 0; i < nbVertices; i++)
  {
    Vector4 vertice = VERTICES.at(i);
    glVertices.insert(glVertices.end(), {vertice.X, vertice.Y, vertice.Z});
    Vector3 verticeTexture = UVS.at(i);
    glVertices.insert(glVertices.end(), {verticeTexture.X, verticeTexture.Y});
  }

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * glVertices.size(), glVertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * INDICES.size(), INDICES.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void Object::draw(Shader currentShader)
{
  currentShader.setMatrix("transform", TRANSLATION * ROTATION);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, INDICES.size(), GL_UNSIGNED_INT, 0);

  currentShader.setMatrix("transform", Matrix4::identity());
}

void Object::deleteBuffers()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}