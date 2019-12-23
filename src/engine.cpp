#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "util.h"

int main() {

    // Initialize OpenGL, GLFW, GLEW, and create a window.
    GLFWwindow *window = init();

    create_program("./src/vertex-shader.glsl", "./src/fragment-shader.glsl");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}