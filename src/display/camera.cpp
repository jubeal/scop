#include "camera.h"

Camera::Camera(Vector4 pos, Vector4 front, Vector4 up, std::string vertexName, std::string fragmentName)
{
  PLAYER_SPEED = 2.5f;
  CAM_SENSITIVITY = 0.1f;
  DELTA_TIME = 0.0f;
  LAST_FRAME = 0.0f;

  MOUSE_X = 400;
  MOUSE_Y = 300;
  YAW = -90.0f;
  PITCH = 0.0f;

  POS = pos;
  FRONT = front;
  UP = up;

  P_SET.fov = 45.0f;
  P_SET.aspect = 800.0f / 600.0f;
  P_SET.near = 0.1f;
  P_SET.far = 100.0f;

  SHADER = Shader(vertexName, fragmentName);

  FREE_CAM = false;

  SHADER.use();
}

void Camera::compute()
{
  float currentFrame = glfwGetTime();
  DELTA_TIME = currentFrame - LAST_FRAME;
  LAST_FRAME = currentFrame;

  SHADER.setMatrix("view", Matrix4::lookAt(POS.toVec3(), (POS + FRONT).toVec3(), UP.toVec3()));
  SHADER.setMatrix("projection", Matrix4::perspective(P_SET.fov, P_SET.aspect, P_SET.near, P_SET.far));
}

void Camera::remove()
{
  SHADER.deleteProgram();
}

void Camera::move(Vector3 dir)
{
  Vector4 forward = (FRONT * (PLAYER_SPEED * DELTA_TIME)) * dir.X;
  Vector4 right = (FRONT.toVec3().cross(UP.toVec3()).normalize().toVec4(0.0f) * (PLAYER_SPEED * DELTA_TIME)) * dir.Y;
  Vector4 up = (UP * (PLAYER_SPEED * DELTA_TIME)) * dir.Z;

  POS = POS + forward + right + up;
}