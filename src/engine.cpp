#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "util.h"

int main() {

    // Initialize OpenGL, GLFW, GLEW, and create a window.
    GLFWwindow *window = init();

    // Specify the vertex and fragment shaders,
    GLuint program_id = create_program(
        "./src/vertex-shader.glsl",
        "./src/fragment-shader.glsl");

    if (!program_id) return 0;

    glUseProgram(program_id);

    // - - - - - - - - - - - TEST AREA - - - - - - - - - - - 

    glClearColor(0, .1, 1, 1);

    GLfloat buf_data[] = {
        .0, .0,
        .9, .9,
        .9, -.9
    };

    GLuint buf_id = 0;
    glCreateBuffers(1, &buf_id);

    glBindBuffer(GL_ARRAY_BUFFER, buf_id);

    glBufferData(GL_ARRAY_BUFFER, sizeof(buf_data), buf_data,
        GL_STATIC_DRAW);

    GLint position_index = glGetAttribLocation(program_id, "vPosition");

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    printf("position location: %d\n", position_index);

    // - - - - - - - - - - END TEST AREA - - - - - - - - - -

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}