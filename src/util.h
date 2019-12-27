/**
 * This file contains some utilities to keep out of the main file while
 * learning opengl. Its not really that organized but it's a place where
 * useful code can go so we can reuse it in the future.
 * 
 */

#ifndef ENGINE_UTIL_H
#define ENGINE_UTIL_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <alloca.h>

using namespace std;

// Used for error handling. Checks the state of glGetError after every call
// to opengl.
#define WRAP_GL(stmt) stmt; \
poll_errors(#stmt, __FILE__, __LINE__);

#define POINTER_OFFSET(class, field) ((const GLvoid *) offsetof(class, field))

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLDBLACK "\033[1m\033[30m"
#define BOLDRED "\033[1m\033[31m"
#define BOLDGREEN "\033[1m\033[32m"
#define BOLDYELLOW "\033[1m\033[33m"
#define BOLDBLUE "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN "\033[1m\033[36m"
#define BOLDWHITE "\033[1m\033[37m"

// Some strings for error output.
const char STR_GL_NO_ERROR[] = "GL_NO_ERROR";
const char STR_GL_INVALID_ENUM[] = "GL_INVALID_ENUM";
const char STR_GL_INVALID_VALUE[] = "GL_INVALID_VALUE";
const char STR_GL_INVALID_OPERATION[] = "GL_INVALID_OPERATION";
const char STR_GL_STACK_OVERFLOW[] = "GL_STACK_OVERFLOW";
const char STR_GL_STACK_UNDERFLOW[] = "GL_STACK_UNDERFLOW";
const char STR_GL_OUT_OF_MEMORY[] = "GL_OUT_OF_MEMORY";
const char STR_GL_INVALID_FRAMEBUFFER_OPERATION[] = "GL_INVALID_FRAMEBUFFER_"
    "OPERATION";
const char STR_GL_CONTEXT_LOST[] = "GL_CONTEXT_LOST";

/**
 * Get the string value of an opengl error enum.
 */
const char *get_err_str(GLenum err) {
    switch (err) {
        case GL_NO_ERROR: return STR_GL_NO_ERROR;
        case GL_INVALID_ENUM: return STR_GL_INVALID_ENUM;
        case GL_INVALID_VALUE: return STR_GL_INVALID_VALUE;
        case GL_INVALID_OPERATION: return STR_GL_INVALID_OPERATION;
        case GL_STACK_OVERFLOW: return STR_GL_STACK_OVERFLOW;
        case GL_STACK_UNDERFLOW: return STR_GL_STACK_UNDERFLOW;
        case GL_OUT_OF_MEMORY: return STR_GL_OUT_OF_MEMORY;
        case GL_INVALID_FRAMEBUFFER_OPERATION: return
            STR_GL_INVALID_FRAMEBUFFER_OPERATION;
        case GL_CONTEXT_LOST: return STR_GL_CONTEXT_LOST;
        default: return nullptr;
    }
}


/**
 * 
 */
void poll_errors(const char *stmt, const char *filename, unsigned int line) {
    GLenum err;
    if ((err = glGetError()) != GL_NO_ERROR) {
        fprintf(stderr, "error: opengl: %s\n" BOLDWHITE " %s:%d  " RED "%s"
            RESET "\n\n", get_err_str(err), filename, line, stmt);
        throw runtime_error(get_err_str(err));
    }
}

/**
 * GLFW Error callback function. Simply prints to stderr.
 */
void glfw_error_func(int error, const char *description) {
    fprintf(stderr, "error: glfw: %d, %s\n", error, description);
}

/**
 * Initialize opengl and glew, create and return a window object.
 */
GLFWwindow *init() {

    // Set the error callback before trying to init.
    glfwSetErrorCallback(glfw_error_func);

    if (!glfwInit()) {
        fprintf(stderr, "error: glfwInit failed.\n");
        return nullptr;
    }

    // Request OpenGL 4.5 with core profile.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(2*640, 2*480, "test window", NULL, NULL);

    if (!window) {
        fprintf(stderr, "error: glfwCreateWindow failed.\n");
        return nullptr;
    }

    // Make the window context the current context.
    glfwMakeContextCurrent(window);

    // Now that a GL context has been created, initialize glew.
    const GLenum glew_err = glewInit();

    if (glew_err != GLEW_OK) {
        fprintf(stderr, "error: glewInit failed: %s.\n",
            glewGetErrorString(glew_err));
        return nullptr;
    }

    // Print out some helpful version information.
    fprintf(stderr, "opengl: %s\nglsl: %s\n\n",
        glGetString(GL_VERSION),
        glGetString(GL_SHADING_LANGUAGE_VERSION));

    return window;
}

/**
 * Just read in a file as a string.
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

    // Check the compile status to report any errors.
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compile_status);

    if (compile_status == GL_FALSE) {
        int log_len = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);

        fprintf(stderr, "error: cannot compile shader\n%s:",
            filename.c_str());

        if (log_len) {
            GLchar *log = (GLchar *) alloca(log_len);
            glGetShaderInfoLog(shader_id, log_len, nullptr, log);
            fprintf(stderr, "%s", log);
        } else {
            fprintf(stderr, "no info log found!\n");
        }
        
        // Delete the shader
        glDeleteShader(shader_id);
        return 0;
     }

    return shader_id;
}


/**
 *
 */
GLuint create_program(const string &vert_src_file, const string &frag_src_file) {
    GLuint vert_shader_id = 0;
    GLuint frag_shader_id = 0;
    GLuint program_id = glCreateProgram();
    GLint link_status = 0;

    // Compile vetex shader and attach if successful.
    vert_shader_id = compile_shader_file(GL_VERTEX_SHADER, vert_src_file);
    if (vert_shader_id) glAttachShader(program_id, vert_shader_id);

    // Compile fragment shader and attach if successful.
    frag_shader_id = compile_shader_file(GL_FRAGMENT_SHADER, frag_src_file);
    if (frag_shader_id) glAttachShader(program_id, frag_shader_id);

    // Link the program.
    glLinkProgram(program_id);

    // If there was an error, then print out useful info.
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
    if (link_status == GL_FALSE) {
        int log_len = 0;
        glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_len);

        fprintf(stderr, "error: cannot link program:\n");

        if (log_len) {
            GLchar *log = (GLchar *) alloca(log_len*sizeof(GLchar));
            glGetProgramInfoLog(program_id, log_len, nullptr, log);
            fprintf(stderr, "%s\n", log);
        } else { 
            fprintf(stderr, "no info log found!\n");
        }

        glDeleteProgram(program_id);
        return 0;
    }

    return program_id;
}

#endif