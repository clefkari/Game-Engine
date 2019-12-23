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
string read_file(string filename) {
    ifstream in(filename);
    istreambuf_iterator<char> begin(in), end;
    return string(begin, end);
}

/**
 * 
 */
const string shader_type_str(GLenum type) {
    switch (type) {
        case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";
        default:
        case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
    }
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
        string sh_type = shader_type_str(type);
        fprintf(stderr, "error: unable to create shader with type %s\n",
            sh_type.c_str());
        return 0;
    }
    
    glShaderSource(shader_id, 1, source_c_str, source_len);
    glCompileShader(shader_id);
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

    if (compile_status != GL_TRUE) {
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

    if (link_status != GL_TRUE) {
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

/**
 * 
 */
GLFWwindow *init() {
    if (!glfwInit()) {
        fprintf(stderr, "error: glfwInit failed.\n");
        return nullptr;
    }

    GLFWwindow *window = glfwCreateWindow(640, 480, "test window", NULL, NULL);

    if (!window) {
        fprintf(stderr, "error: glfwCreateWindow failed.\n");
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "error: glewInit failed.\n");
        return nullptr;
    }

    return window;
}

#endif