#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include <iostream>

using namespace std;

#include "util.h"
#include "math/vec.hpp"

int main() {
    // Initialize OpenGL, GLFW, GLEW, and create a window.
    GLFWwindow *window = init();

    // Specify the vertex and fragment shaders,
    GLuint program_id = create_program(
        "./src/vertex-shader.glsl",
        "./src/fragment-shader.glsl");

    if (!program_id)
        return 0;

    WRAP_GL( glUseProgram(program_id) );

    struct Vertex {
        vec2 position;
        vec4 color;
    };

    // Vertex and index data.
    Vertex verts[] = {
        { {-.9, .9},  {1, 0, 0, 1} },
        { {.9, .9},   {0, 1, 0, 1} },
        { {-.9, -.9}, {0, 0, 1, 1} },
        { {.9, -.9},  {0, 1, 1, 1} }
    };

    GLuint indices[] = { 0, 1, 2, 3 };

    // The number of each type of object to create.
    const int num_vaos = 1, num_vbos = 1, num_ibos = 1;

    // Arrays to store object ids.
    GLuint vaos[num_vaos], vbos[num_vbos], ibos[num_ibos];

    // Generate buffers and vertex arrays.
    WRAP_GL( glGenVertexArrays(num_vaos, vaos) );
    WRAP_GL( glGenBuffers(num_vbos, vbos) );
    WRAP_GL( glGenBuffers(num_ibos, ibos) );

    // Bind the vertex array.
    WRAP_GL( glBindVertexArray(vaos[0]) );

    // Bind the vertex buffer and load vertex data.
    WRAP_GL( glBindBuffer(GL_ARRAY_BUFFER, vbos[0]) );
    WRAP_GL( glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts,
        GL_STATIC_DRAW) );

    // Tell OpenGL about the position attribute.
    GLint loc = -1;

    WRAP_GL( loc = glGetAttribLocation(program_id, "vPosition") );
    WRAP_GL( glEnableVertexAttribArray(loc) );
    WRAP_GL( glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        OFFSET_CLASS(Vertex, position)) );

    // Tell OpenGL about the color attribute.
    WRAP_GL( loc = glGetAttribLocation(program_id, "vColor") );
    WRAP_GL( glEnableVertexAttribArray(loc) );
    WRAP_GL( glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        OFFSET_CLASS(Vertex, color)) );

    loc = glGetUniformLocation(program_id, "uTime");


    // Bind the index buffer and load index data.
    WRAP_GL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[0]) );
    WRAP_GL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
        GL_STATIC_DRAW) );

    float t = 0;

    while (!glfwWindowShouldClose(window)) {

        WRAP_GL( glUniform1f(loc, t) );
        WRAP_GL( glClear(GL_COLOR_BUFFER_BIT) );
        WRAP_GL( glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0) );

        glfwSwapBuffers(window);
        glfwPollEvents();

        t += 0.003;
    }

    glfwTerminate();
    return 0;
}