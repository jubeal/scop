#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "logs.h"

#include "objects.h"
#include "camera.h"
#include "texture.h"
#include "shaders.h"

#include "inputs.h"
#include "vector.h"
#include "matrix.h"

#include "parsing.h"

GLFWwindow *createGlfwWindow();
void framebufferSizeCallback(GLFWwindow *window, int width, int height);