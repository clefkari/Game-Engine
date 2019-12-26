#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "util.h"

#define WRAP_GL(stmt) stmt; \
pollErrors(#stmt, __FILE__, __LINE__);

void pollErrors(const char *stmt, const char *filename, unsigned int line) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "error: opengl: %s\n" BOLDWHITE " %s:%d  " RED "%s" 
            RESET "\n\n", get_err_str(err), filename, line, stmt);
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

    float verts_a[] = {0,  0,    1,  1,   -1,  1};
    float verts_b[] = {0,  0,    1,  -1,   -1,  -1};

    const int num_vaos = 2, num_vbos = 2;
    GLuint vaos[num_vaos], vbos[num_vbos];

    WRAP_GL( glGenVertexArrays(num_vaos, vaos) );
    WRAP_GL( glGenBuffers(num_vbos, vbos) );

    WRAP_GL( glBindVertexArray(vaos[0]) );
    WRAP_GL( glBindBuffer(GL_ARRAY_BUFFER, vbos[0]) );
    WRAP_GL( glEnableVertexAttribArray(0) );
    WRAP_GL( glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0) );
    WRAP_GL( glBufferData(GL_ARRAY_BUFFER, sizeof(verts_a), verts_a, GL_STATIC_DRAW) );


    WRAP_GL( glBindVertexArray(vaos[1]) );
    WRAP_GL( glBindBuffer(GL_ARRAY_BUFFER, vbos[1]) );
    WRAP_GL( glEnableVertexAttribArray(0) );
    WRAP_GL( glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0) );
    WRAP_GL( glBufferData(GL_ARRAY_BUFFER, sizeof(verts_b), verts_b, GL_STATIC_DRAW) );

    int i = 0;
    int j = 0;

    while (!glfwWindowShouldClose(window)) {
        WRAP_GL(glClear(GL_COLOR_BUFFER_BIT));

        if (i++%50 == 0) {
            int b = j++ % 2;
            WRAP_GL( glBindVertexArray(vaos[b]) );
            WRAP_GL( glBindBuffer(GL_ARRAY_BUFFER, vbos[b]) );
        }

        WRAP_GL( glDrawArrays(GL_TRIANGLES, 0, 3) );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}