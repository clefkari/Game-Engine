/**
 * This file contains some utilities to keep out of the main file while
 * 
 */

#ifndef ENGINE_UTIL_H
#define ENGINE_UTIL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;

/**
 * 
 */
GLFWwindow *init() {
    if (!glfwInit()) {
        fprintf(stderr, "error: glfwInit failed.\n");
        return nullptr;
    }

    // Request OpenGL 4.5 with core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(640, 480, "test window", NULL, NULL);

    if (!window) {
        fprintf(stderr, "error: glfwCreateWindow failed.\n");
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    const GLenum glew_err = glewInit();

    if (glew_err != GLEW_OK) {
        fprintf(stderr, "error: glewInit failed: %s.\n",
            glewGetErrorString(glew_err));
        return nullptr;
    }

    //
    fprintf(stderr, "version: %s\n", glGetString(GL_VERSION));

    return window;
}

/**
 * 
 */
string read_file(string filename) {
    ifstream in(filename);
    istreambuf_iterator<char> begin(in), end;
    return string(begin, end);
}

/**
 * 
 */
GLuint compile_shader_file(GLenum type, const string &filename) {

    // Create a new empty shader and save its id.
    GLuint shader_id = glCreateShader(type);

    // For retrieving the status of compilation.
    GLint compile_status = GL_FALSE;

    // Read the entire file contents into a string.
    string source = read_file(filename);

    // The source code as a size 1 array of strings.
    const GLchar *source_c_str[] = {source.c_str()};

    // The size of each string in the previous array.
    const GLint source_len[] = {(GLint) source.size()};

    if (!shader_id) {
        fprintf(stderr, "error: unable to create shader for file %s\n",
            filename.c_str());
        return 0;
    }
    
    glShaderSource(shader_id, 1, source_c_str, source_len);
    glCompileShader(shader_id);
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

    // If there was an error, then print out useful info.
    if (compile_status == GL_FALSE) {
        int log_len = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);

        fprintf(stderr, "error: cannot compile shader from file '%s':\n",
            filename.c_str());

        if (log_len) {
            char *log = new char[log_len];
            glGetShaderInfoLog(shader_id, log_len, nullptr, log);
            fprintf(stderr, "%s\n", log);
            delete[] log;
        } else { 
            fprintf(stderr, "no info log found.\n");
        }

        glDeleteShader(shader_id);
        return 0;
     }

    return shader_id;
}

/**
 * 
 */
GLuint create_program(const string &vert_src_file, const string &frag_src_file) {
    GLuint program_id = glCreateProgram();

    GLint link_status = 0;
    GLuint vert_shader_id = 0;
    GLuint frag_shader_id = 0;

    vert_shader_id = compile_shader_file(GL_VERTEX_SHADER, vert_src_file);

    if (vert_shader_id)
        glAttachShader(program_id, vert_shader_id);

    frag_shader_id = compile_shader_file(GL_FRAGMENT_SHADER, frag_src_file);

    if (frag_shader_id)
        glAttachShader(program_id, frag_shader_id);

    glLinkProgram(program_id);

    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);

    // If there was an error, then print out useful info.
    if (link_status == GL_FALSE) {
        int log_len = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_len);

        fprintf(stderr, "error: cannot link program:\n");

        if (log_len) {
            char *log = new char[log_len];
            glGetProgramInfoLog(program_id, log_len, nullptr, log);
            fprintf(stderr, "%s\n", log);
            delete[] log;
        } else { 
            fprintf(stderr, "no info log found.\n");
        }

        glDeleteProgram(program_id);
        return 0;
    }

    return program_id;
}

#endif