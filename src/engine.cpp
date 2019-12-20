#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

using namespace std;

int main() {

    GLFWwindow *window = nullptr;

    cout << "glfwInit: " << (glfwInit() == GLFW_TRUE ? "yes" : "no") << endl;

    window = glfwCreateWindow(500, 300, "My Test", NULL, NULL);

    cout << "window: " << window << endl;

    glfwMakeContextCurrent(window);

    //glTexImage2D(GL_TEXTURE2D, 0, GL_RGBA8, 10, 10, 0, GL_RGBA, GL_UNSIGNED_BYTE, ptrToPixelBuf);

    cout << "glewInit: " << (glewInit() == GLEW_OK ? "yes" : "no") << endl;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);

        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(0.5f, -0.5f);

        glEnd();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
