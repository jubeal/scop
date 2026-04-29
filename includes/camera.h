#pragma once

#include <vector>

#include "logs.h"
#include "matrix.h"
#include "vector.h"
#include "shaders.h"

struct ProjectionSettings
{
  float fov;
  float aspect;
  float near;
  float far;
};

class Camera
{
public:
  float PLAYER_SPEED;
  float CAM_SENSITIVITY;
  float DELTA_TIME;
  float LAST_FRAME;

  int MOUSE_X;
  int MOUSE_Y;
  float YAW;
  float PITCH;

  Vector4 POS;
  Vector4 FRONT;
  Vector4 UP;

  ProjectionSettings P_SET;
  Shader SHADER;

  bool FREE_CAM;

  Camera(Vector4 pos, Vector4 front, Vector4 up, std::string vertexName = "default", std::string fragmentName = "default");

  void compute();
  void remove();

  void move(Vector3 dir);
};