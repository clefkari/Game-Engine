#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;

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
GLuint create_shader(GLenum type, const string &source) {

    // Create a new empty shader and save its id.
    GLuint shader_id = glCreateShader(type);

    // For retrieving the status of compilation.
    GLint compile_status = GL_FALSE;

    // The source code as a size 1 array of strings.
    const char *source_c_str[] = {source.c_str()};

    // The size of each string in the previous array.
    const int source_len[] = {source.size()};

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

        fprintf(stderr, "error: cannot compile shader:\n");

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

GLuint create_program(const string &vert_source_file, const string &frag_source_file) {
    string vert_source = read_file(vert_source_file);
    string frag_source = read_file(frag_source_file);
    GLuint program_id = glCreateProgram();

    GLint link_status = 0;

    int vert_shader_id = 0, frag_shader_id = 0;

    if (vert_shader_id = create_shader(GL_VERTEX_SHADER, vert_source))
        glAttachShader(program_id, vert_shader_id);

    if (frag_shader_id = create_shader(GL_FRAGMENT_SHADER, frag_source))
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

int main(int argc, char *argv[]) {
    return 0;
}