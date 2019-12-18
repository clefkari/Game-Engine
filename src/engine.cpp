#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

int main() {

    GLFWwindow *window = nullptr;

    cout << "glfwInit: " << (glfwInit() == GLFW_TRUE ? "yes" : "no") << endl;

    window = glfwCreateWindow(500, 300, "My Test", NULL, NULL);

    cout << "window: " << window << endl;
    cout << "context: " << glfwGetCurrentContext() << endl;

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
