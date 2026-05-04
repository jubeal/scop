#include "inputs.h"

void processInput(GLFWwindow *window)
{
  CustomWindowPointer *wPointer = static_cast<CustomWindowPointer *>(glfwGetWindowUserPointer(window));
  Vector3 direction(0, 0, 0);

  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    direction.Y += 0.1f;

  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    direction.Y -= 0.1f;

  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    direction.X -= 0.1f;

  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    direction.X += 0.1f;

  if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
    direction.Z -= 0.1f;

  if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
    direction.Z += 0.1f;
  
  if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
    wPointer->textureAlpha = wPointer->textureAlpha > 0.0f ? wPointer->textureAlpha - 0.01f : 0.0f;
  
  if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
    wPointer->textureAlpha = wPointer->textureAlpha < 1.0f ? wPointer->textureAlpha + 0.01f : 1.0f;

  wPointer->objectList.at(wPointer->currentObjectIndex).translate(direction.toVec4(1));

  if (!wPointer->cam->FREE_CAM)
    return;
  direction = {0, 0, 0};

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    direction.X += 1;

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    direction.Y -= 1;

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    direction.X -= 1;

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    direction.Y += 1;

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    direction.Z += 1;

  if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    direction.Z -= 1;

  wPointer->cam->move(direction);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  (void)scancode;
  (void)mods;

  if (action != GLFW_RELEASE)
    return;

  CustomWindowPointer *wPointer = static_cast<CustomWindowPointer *>(glfwGetWindowUserPointer(window));

  switch (key)
  {
  case GLFW_KEY_ESCAPE:
    glfwSetWindowShouldClose(window, true);
    break;
  case GLFW_KEY_0:
    wPointer->objectRotationSpeed = 0.0f;
    break;
  case GLFW_KEY_1:
    wPointer->objectRotationSpeed = 0.1f;
    break;
  case GLFW_KEY_2:
    wPointer->objectRotationSpeed = 0.3f;
    break;
  case GLFW_KEY_3:
    wPointer->objectRotationSpeed = 0.6f;
    break;
  case GLFW_KEY_I:
    wPointer->objectRotationDirection *= -1;
    break;
  case GLFW_KEY_F:
    wPointer->cam->FREE_CAM = !wPointer->cam->FREE_CAM;
    break;
  case GLFW_KEY_O:
    if (wPointer->currentObjectIndex >= wPointer->objectList.size() - 1)
      wPointer->currentObjectIndex = 0;
    else
      wPointer->currentObjectIndex += 1;
    break;
  }
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos)
{
  Camera *cam = static_cast<CustomWindowPointer *>(glfwGetWindowUserPointer(window))->cam;

  if (!cam->FREE_CAM)
    return;

  float xoffset = xpos - cam->MOUSE_X;
  float yoffset = ypos - cam->MOUSE_Y;

  cam->MOUSE_X = xpos;
  cam->MOUSE_Y = ypos;

  xoffset *= cam->CAM_SENSITIVITY;
  yoffset *= cam->CAM_SENSITIVITY;

  cam->YAW += xoffset;
  cam->PITCH -= yoffset;
  // prevent 360 vertical rotation
  if (cam->PITCH > 89.0f)
    cam->PITCH = 89.0f;
  if (cam->PITCH < -89.0f)
    cam->PITCH = -89.0f;

  Vector3 direction;
  float radiansYaw = cam->YAW * (Constants::PI / 180.0f);
  float radiansPitch = cam->PITCH * (Constants::PI / 180.0f);

  direction.X = std::cos(radiansYaw) * std::cos(radiansPitch);
  direction.Y = std::sin(radiansPitch);
  direction.Z = std::sin(radiansYaw) * std::cos(radiansPitch);

  cam->FRONT = direction.normalize().toVec4(0.0f);
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
  Camera *cam = static_cast<CustomWindowPointer *>(glfwGetWindowUserPointer(window))->cam;
  (void)xoffset;

  if (!cam->FREE_CAM)
    return;

  cam->P_SET.fov -= (float)yoffset;

  if (cam->P_SET.fov < 1.0f)
    cam->P_SET.fov = 1.0f;
  if (cam->P_SET.fov > 90.0f)
    cam->P_SET.fov = 90.0f;
}