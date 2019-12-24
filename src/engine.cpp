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

    glClearColor(0, 0, 0.3, 1);

    GLfloat vertex_data[] = {
        .0, .0,
        .9, .9,
        -.9, .9
    };

    GLuint vertex_array_id = 0, buffer_id = 0;

    glGenVertexArrays(1, &vertex_array_id);

    glBindVertexArray(vertex_array_id);

    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data,
        GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);
    glEnableVertexAttribArray(0);

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