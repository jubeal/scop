#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <vector.h>

#include "constants.h"
#include "camera.h"
#include "objects.h"

struct CustomWindowPointer
{
  Camera *cam;
  float objectRotationSpeed;
  int objectRotationDirection;
  Vector3 objectRotationAxis;
  unsigned int currentObjectIndex;
  std::vector<Object> objectList;
};

void processInput(GLFWwindow *window);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
