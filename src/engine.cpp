#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "util.h"

#define WRAP_GL(stmt) stmt; \
pollErrors(#stmt, __FILE__, __LINE__);


void pollErrors(const char *stmt, const char *filename, unsigned int line) {
    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "error: opengl: %s\n" BOLDWHITE " %s:%d  " RED "%s"
            RESET "\n\n", get_err_str(err), filename, line, stmt);
        throw runtime_error(get_err_str(err));
    }
}


int main() {
    // Initialize OpenGL, GLFW, GLEW, and create a window.
    GLFWwindow *window = init();
    // Specify the vertex and fragment shaders,
    GLuint program_id = create_program(
        "./src/vertex-shader.glsl",
        "./src/fragment-shader.glsl");
    if (!program_id) return 0;
    WRAP_GL(glUseProgram(program_id));

    GLfloat verts[] = { 0,0,  1,0,  1,1,  0,1 };

    GLuint indices[] = { 0, 1, 2, 3 };

    const int num_vaos = 2, num_vbos = 2, num_ibos = 1;
    GLuint vaos[num_vaos], vbos[num_vbos], ibos[num_ibos];

    WRAP_GL( glGenVertexArrays(num_vaos, vaos) );
    WRAP_GL( glGenBuffers(num_vbos, vbos) );
    WRAP_GL( glGenBuffers(num_ibos, ibos) );

    fprintf(stderr, "vaos: %d %d\n", vaos[0], vaos[1]);
    fprintf(stderr, "vbos: %d %d\n", vbos[0], vbos[1]);
    fprintf(stderr, "ibos: %d\n\n", ibos[0]);

    WRAP_GL( glBindVertexArray(vaos[0]) );
    WRAP_GL( glBindBuffer(GL_ARRAY_BUFFER, vbos[0]) );
    WRAP_GL( glEnableVertexAttribArray(0) );
    WRAP_GL( glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0) );
    WRAP_GL( glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts,
        GL_STATIC_DRAW) );

    WRAP_GL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[0]) );
    WRAP_GL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
        GL_STATIC_DRAW) );

    while (!glfwWindowShouldClose(window)) {

        WRAP_GL( glClear(GL_COLOR_BUFFER_BIT) );
        WRAP_GL( glDrawArrays(GL_TRIANGLES, 0, 3) );

        WRAP_GL( glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0) );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}