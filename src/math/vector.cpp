#include "vector.h"

Vector2::Vector2(float x, float y)
{
  X = x;
  Y = y;
}

Vector2::Vector2(float coords[2])
{
  X = coords[0];
  Y = coords[1];
}

Vector3::Vector3(float x, float y, float z)
{
  X = x;
  Y = y;
  Z = z;
}

Vector3::Vector3(float coords[3])
{
  X = coords[0];
  Y = coords[1];
  Z = coords[3];
}

Vector3 Vector3::operator+(Vector3 &vec) const
{
  Vector3 result;

  result.X = X + vec.X;
  result.Y = Y + vec.Y;
  result.Z = Z + vec.Z;

  return result;
}

Vector3 Vector3::operator-(Vector3 &vec) const
{
  Vector3 result;

  result.X = X - vec.X;
  result.Y = Y - vec.Y;
  result.Z = Z - vec.Z;

  return result;
}

Vector3 Vector3::cross(Vector3 factor)
{
  Vector3 result;

  result.X = Y * factor.Z - Z * factor.Y;
  result.Y = Z * factor.X - X * factor.Z;
  result.Z = X * factor.Y - Y * factor.X;

  return result;
}

float Vector3::dot(Vector3 factor)
{
  return (X * factor.X + Y * factor.Y + Z * factor.Z);
}

Vector3 Vector3::normalize()
{
  float magnitude;

  magnitude = std::sqrt(X * X + Y * Y + Z * Z);
  if (magnitude == 0.0f)
    return Vector3(0.0f, 0.0f, 0.0f);

  return Vector3(
      X / magnitude,
      Y / magnitude,
      Z / magnitude);
}

Vector4 Vector3::toVec4(float w)
{
  return Vector4(X, Y, Z, w);
}

Vector4::Vector4(float x, float y, float z, float w)
{
  X = x;
  Y = y;
  Z = z;
  W = w;
}

Vector4::Vector4(float coords[4])
{
  X = coords[0];
  Y = coords[1];
  Z = coords[2];
  W = coords[3];
}

Vector4 Vector4::operator+(Vector4 &vec) const
{
  Vector4 result;

  result.X = X + vec.X;
  result.Y = Y + vec.Y;
  result.Z = Z + vec.Z;
  result.W = W + vec.W;

  return result;
}

Vector4 Vector4::operator-(Vector4 &vec) const
{
  Vector4 result;

  result.X = X - vec.X;
  result.Y = Y - vec.Y;
  result.Z = Z - vec.Z;
  result.W = W - vec.W;

  return result;
}

Vector4 Vector4::operator*(float factor) const
{
  Vector4 result;

  result.X = X * factor;
  result.Y = Y * factor;
  result.Z = Z * factor;
  result.W = W * factor;

  return result;
}

Vector4 Vector4::operator*(Matrix4 &mat) const
{
  Vector4 result;

  result.X = mat.M[0][0] * X + mat.M[0][1] * Y + mat.M[0][2] * Z + mat.M[0][3] * W;
  result.Y = mat.M[1][0] * X + mat.M[1][1] * Y + mat.M[1][2] * Z + mat.M[1][3] * W;
  result.Z = mat.M[2][0] * X + mat.M[2][1] * Y + mat.M[2][2] * Z + mat.M[2][3] * W;
  result.W = mat.M[3][0] * X + mat.M[3][1] * Y + mat.M[3][2] * Z + mat.M[3][3] * W;

  if (result.W != 1.0f)
  {
    result.X /= result.W;
    result.Y /= result.W;
    result.Z /= result.W;
    result.W = 1.0f;
  }

  return result;
}

Vector4 Vector4::normalize()
{
  float magnitude;

  magnitude = std::sqrt(X * X + Y * Y + Z * Z);

  if (magnitude == 0.0f)
    return Vector4(0.0f, 0.0f, 0.0f, W);

  return Vector4(X / magnitude, Y / magnitude, Z / magnitude, W);
}

Vector3 Vector4::toVec3()
{
  return Vector3(X, Y, Z);
}
