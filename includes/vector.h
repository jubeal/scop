#pragma once

#include <cmath>

#include "matrix.h"

class Matrix4;

class Vector2
{
public:
  float X;
  float Y;

  Vector2(float x = 0.0f, float y = 0.0f);
  Vector2(float coords[2]);
};

class Vector4;

class Vector3
{
public:
  float X;
  float Y;
  float Z;

  Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
  Vector3(float coords[3]);

  Vector3 operator+(Vector3 &vec) const;
  Vector3 operator-(Vector3 &vec) const;

  Vector3 cross(Vector3 factor);
  float dot(Vector3 factor);
  Vector3 normalize();
  Vector4 toVec4(float w);
};

class Vector4
{
public:
  float X;
  float Y;
  float Z;
  float W;

  Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
  Vector4(float coords[4]);

  Vector4 operator+(Vector4 &vec) const;
  Vector4 operator-(Vector4 &vec) const;
  Vector4 operator*(float factor) const;
  Vector4 operator*(Matrix4 &mat) const;

  Vector4 normalize();
  Vector3 toVec3();
};