#include "main.h"

int main()
{
  try
  {
    //initiate program
    GLFWwindow *window = createGlfwWindow();

    if (window == NULL)
    {
      logError("ERROR::INITIALIZATION:", "Could not create GLFW window");
      glfwTerminate();
      throw -300;
    }

    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    Camera cam = Camera(Vector4(0.0f, 0.0f, 6.0f, 1.0f), Vector4(0.0f, 0.0f, -1.0f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f));

    std::vector<std::string> objFilesPaths = getObjFiles();
    std::vector<Object> objectList;
    for (const std::string &file : objFilesPaths)
    {
      objectList.push_back(Object(file, Vector4(0, 0, 0, 1)));
      objectList.back().compute();
    }

    //creating the custom pointer to send to inputs
    CustomWindowPointer wPointer = {
        &cam,
        0.1f,
        1,
        Vector3(0, 1, 0),
        0,
        objectList,
    };

    if (wPointer.objectList.empty())
    {
      cam.remove();
      glfwTerminate();
      logError("ERROR::INITIALIZATION:", "No .obj files found. Please provide at least 1 file in ./resources/objects");
      throw -300;
    }

    glfwSetWindowUserPointer(window, &wPointer);

    Texture poney("./resources/textures/poney.bmp");

    while (!glfwWindowShouldClose(window))
    {
      // Object currentObject = wPointer.objectList.at(wPointer.currentObjectIndex);
      // First process inputs
      processInput(window);

      // clear last image
      glClearColor(0.36f, 0.36f, 0.39f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // Then render everything
      cam.compute();

      wPointer.objectList.at(wPointer.currentObjectIndex).draw(cam.SHADER);

      wPointer.objectList.at(wPointer.currentObjectIndex).rotate(wPointer.objectRotationAxis, wPointer.objectRotationSpeed, wPointer.objectRotationDirection);

      poney.use();

      // Finally listen to events and display on window
      glfwPollEvents();
      glfwSwapBuffers(window);
    }

    cam.remove();
    for (Object obj : wPointer.objectList)
      obj.deleteBuffers();
    poney.deleteTexture();

    glfwTerminate();

    return 0;
  }
  catch (int error)
  {
    if (error == -300)
      return -1;

    logError("ERROR::UKNOWN:", "Error code " + std::to_string(error));
    return -1;
  }
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
  (void)window;
  glViewport(0, 0, width, height);
}

GLFWwindow *createGlfwWindow()
{
  // Configurate GLFW window to work with OpenGL
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create Window
  GLFWwindow *window = glfwCreateWindow(800, 600, "Scop", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    return NULL;
  }

  glfwMakeContextCurrent(window);

  // Use GLAD to find and use the correct OpenGL functions depending on the computer
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return NULL;
  }

  // Resize viewport to match window resize
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  return window;
}