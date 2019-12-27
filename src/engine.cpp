#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include <iostream>
#include <vector>

#include "util.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

using namespace std;


int main() {
    // Initialize OpenGL, GLFW, GLEW, and create a window.
    GLFWwindow *window = init();

    // Specify the vertex and fragment shaders,
    GLuint program_id = create_program(
        "./src/vertex-shader.glsl",
        "./src/fragment-shader.glsl");

    WRAP_GL( glUseProgram(program_id) );

    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };

    // Image loading test (for textures)
    int im_width = 0, im_height = 0, im_n = 0;
    unsigned char *image = stbi_load("./src/test-image.png", &im_width,
        &im_height, &im_n, 0);
    printf("x=%d, y=%d, n=%d\n", im_width, im_height, im_n);

    stbi_image_free(image);
    
    

    // Vertex and index data.
    Vertex verts[6*2*3] = {
        {{0, 0, 1},  {.5, .5, .5}},
        {{1, 0, 1},  {0, 0, 1}},
        {{0, 1, 1},  {0, 1, 0}},
        {{1, 1, 1},  {0, 1, 1}},
        {{0, 0, 0},  {1, 0, 0}},
        {{1, 0, 0},  {1, 0, 1}},
        {{0, 1, 0},  {1, 1, 0}},
        {{1, 1, 0},  {1, 1, 1}},
    };
    GLuint indices[] = { 0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1 };

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

    // Location of variables in the shader program.
    GLint loc = -1;

    // Tell OpenGL about the position attribute.
    WRAP_GL( loc = glGetAttribLocation(program_id, "vPosition") );
    WRAP_GL( glEnableVertexAttribArray(loc) );
    WRAP_GL( glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        POINTER_OFFSET(Vertex, position)) );

    // Tell OpenGL about the color attribute.
    WRAP_GL( loc = glGetAttribLocation(program_id, "vColor") );
    WRAP_GL( glEnableVertexAttribArray(loc) );
    WRAP_GL( glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        POINTER_OFFSET(Vertex, color)) );

    WRAP_GL( loc = glGetUniformLocation(program_id, "uTime") );

    // Bind the index buffer and load index data.
    WRAP_GL( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibos[0]) );
    WRAP_GL( glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
        GL_STATIC_DRAW) );

    float t = 0, dt = 0;

    while (!glfwWindowShouldClose(window)) {

        // Set the value of the uniform variable.
        WRAP_GL( loc = glGetUniformLocation(program_id, "uTime") );
        WRAP_GL( glUniform1f(glGetUniformLocation(program_id, "uTime"), 0) );

        // Clear the screen.
        WRAP_GL( glClear(GL_COLOR_BUFFER_BIT) );

        float theta = 0, sc = .75;

        glm::vec3 trans = {-.5, -.5, -.5};

        glm::mat4 mvp_mat(1);

        mvp_mat = glm::scale(mvp_mat, glm::vec3(sc, sc, sc));

        mvp_mat = glm::rotate(mvp_mat, t/10, glm::vec3(1, 0, 0));
        mvp_mat = glm::rotate(mvp_mat, t/20, glm::vec3(0, 1, 0));
        mvp_mat = glm::rotate(mvp_mat, t, glm::vec3(0, 0, 1));
        mvp_mat = glm::translate(mvp_mat, trans);

        //mvp_mat = glm::mat4(1);

        WRAP_GL( loc = glGetUniformLocation(program_id, "uModelViewProjection") );
        WRAP_GL( glUniformMatrix4fv(loc, 1, GL_FALSE, (const GLfloat *) &mvp_mat) );


        // Draw a triangle strip according to the index buffer (the list of
        // vertex indices).
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        WRAP_GL( glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_INT, 0) );

        glfwSwapBuffers(window);
        glfwPollEvents();

        t += .01;//dt += (rand()%10 - 5)/100000.;
    }

    glfwTerminate();
    return 0;
}
