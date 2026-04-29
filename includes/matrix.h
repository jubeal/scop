#pragma once

#include <iostream>
#include <cmath>
#include <array>
#include <string>

#include "constants.h"
#include "vector.h"

class Vector3;
class Vector4;

class Matrix4
{
public:
  std::array<std::array<float, 4>, 4> M; // Matrices are row major based

  // Base Matrices
  static Matrix4 identity();
  static Matrix4 scale(float power);
  static Matrix4 translation(Vector4 direction);
  static Matrix4 rotationX(float degrees);
  static Matrix4 rotationY(float degrees);
  static Matrix4 rotationZ(float degrees);
  static Matrix4 orthographic(float left, float right, float bottom, float top, float near, float far);
  static Matrix4 perspective(float fov, float aspect, float near, float far);
  static Matrix4 lookAt(Vector3 pos, Vector3 tar, Vector3 up);

  std::string getDisplayableDatas();

  Matrix4 operator*(const Matrix4 &mat) const;
};