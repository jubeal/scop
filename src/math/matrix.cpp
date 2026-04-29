#include "matrix.h"

Matrix4 Matrix4::identity()
{
  Matrix4 result;

  result.M[0] = {1.0f, 0.0f, 0.0f, 0.0f};
  result.M[1] = {0.0f, 1.0f, 0.0f, 0.0f};
  result.M[2] = {0.0f, 0.0f, 1.0f, 0.0f};
  result.M[3] = {0.0f, 0.0f, 0.0f, 1.0f};

  return result;
}

Matrix4 Matrix4::scale(float power)
{
  Matrix4 result;

  result.M[0] = {power, 0.0f, 0.0f, 0.0f};
  result.M[1] = {0.0f, power, 0.0f, 0.0f};
  result.M[2] = {0.0f, 0.0f, power, 0.0f};
  result.M[3] = {0.0f, 0.0f, 0.0f, 1.0f};

  return result;
}

Matrix4 Matrix4::translation(Vector4 direction)
{
  Matrix4 result;

  result.M[0] = {1.0f, 0.0f, 0.0f, direction.X};
  result.M[1] = {0.0f, 1.0f, 0.0f, direction.Y};
  result.M[2] = {0.0f, 0.0f, 1.0f, direction.Z};
  result.M[3] = {0.0f, 0.0f, 0.0f, 1.0f};

  return result;
}

Matrix4 Matrix4::rotationX(float degrees)
{
  Matrix4 result;

  float radians = degrees * (Constants::PI / 180.0f);
  float cos = std::cos(radians);
  float sin = std::sin(radians);

  result.M[0] = {1.0f, 0.0f, 0.0f, 0.0f};
  result.M[1] = {0.0f, cos, -sin, 0.0f};
  result.M[2] = {0.0f, sin, cos, 0.0f};
  result.M[3] = {0.0f, 0.0f, 0.0f, 1.0f};

  return result;
}

Matrix4 Matrix4::rotationY(float degrees)
{
  Matrix4 result;

  float radians = degrees * (Constants::PI / 180.0f);
  float cos = std::cos(radians);
  float sin = std::sin(radians);

  result.M[0] = {cos, 0.0f, sin, 0.0f};
  result.M[1] = {0.0f, 1.0f, 0.0f, 0.0f};
  result.M[2] = {-sin, 0.0f, cos, 0.0f};
  result.M[3] = {0.0f, 0.0f, 0.0f, 1.0f};

  return result;
}

Matrix4 Matrix4::rotationZ(float degrees)
{
  Matrix4 result;

  float radians = degrees * (Constants::PI / 180.0f);
  float cos = std::cos(radians);
  float sin = std::sin(radians);

  result.M[0] = {cos, -sin, 0.0f, 0.0f};
  result.M[1] = {sin, cos, 0.0f, 0.0f};
  result.M[2] = {0.0f, 0.0f, 1.0f, 0.0f};
  result.M[3] = {0.0f, 0.0f, 0.0f, 1.0f};

  return result;
}

Matrix4 Matrix4::orthographic(float left, float right, float bottom, float top, float near, float far)
{
  Matrix4 result;

  result.M[0] = {2.0f / (right - left), 0.0f, 0.0f, -(right + left) / (right - left)};
  result.M[1] = {0.0f, 2.0f / (top - bottom), 0.0f, -(top + bottom) / (top - bottom)};
  result.M[2] = {0.0f, 0.0f, -2.0f / (far - near), -(far + near) / (far - near)};
  result.M[3] = {0.0f, 0.0f, 0.0f, 1.0f};

  return result;
}

Matrix4 Matrix4::perspective(float fov, float aspect, float near, float far)
{
  Matrix4 result;
  float fovRad = 1.0f / std::tan(fov * (Constants::PI / 180.0f) / 2.0f);

  result.M[0] = {fovRad / aspect, 0.0f, 0.0f, 0.0f};
  result.M[1] = {0.0f, fovRad, 0.0f, 0.0f};
  result.M[2] = {0.0f, 0.0f, (far + near) / (near - far), (2.0f * far * near) / (near - far)};
  result.M[3] = {0.0f, 0.0f, -1.0f, 0.0f};

  return result;
}

Matrix4 Matrix4::lookAt(Vector3 pos, Vector3 tar, Vector3 up)
{
  Matrix4 result;
  Vector3 forward = (pos - tar).normalize();
  Vector3 right = up.cross(forward).normalize();
  Vector3 lookAtUp = forward.cross(right);

  result.M[0] = {right.X, right.Y, right.Z, -right.dot(pos)};
  result.M[1] = {lookAtUp.X, lookAtUp.Y, lookAtUp.Z, -lookAtUp.dot(pos)};
  result.M[2] = {forward.X, forward.Y, forward.Z, -forward.dot(pos)};
  result.M[3] = {0.0f, 0.0f, 0.0f, 1.0f};

  return result;
}

std::string Matrix4::getDisplayableDatas()
{
  std::string result;

  result = "| " + std::to_string(M[0][0]) + " " + std::to_string(M[0][1]) + " " + std::to_string(M[0][2]) + " " + std::to_string(M[0][3]) + " |\n" +
           "| " + std::to_string(M[1][0]) + " " + std::to_string(M[1][1]) + " " + std::to_string(M[1][2]) + " " + std::to_string(M[1][3]) + " |\n" +
           "| " + std::to_string(M[2][0]) + " " + std::to_string(M[2][1]) + " " + std::to_string(M[2][2]) + " " + std::to_string(M[2][3]) + " |\n" +
           "| " + std::to_string(M[3][0]) + " " + std::to_string(M[3][1]) + " " + std::to_string(M[3][2]) + " " + std::to_string(M[3][3]) + " |";

  return result;
}

Matrix4 Matrix4::operator*(const Matrix4 &mat) const
{
  Matrix4 result;

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      result.M[i][j] = M[i][0] * mat.M[0][j] + M[i][1] * mat.M[1][j] + M[i][2] * mat.M[2][j] + M[i][3] * mat.M[3][j];
    }
  }

  return result;
}
