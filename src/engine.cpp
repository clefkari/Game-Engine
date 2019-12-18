#include <GL/glew.h>

#include <SDL2/SDL.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int main() {

    SDL_Window *window;
    SDL_GLContext gl_context;
    SDL_Event sdl_event;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "cannot initialize sdl video" << endl;
        return 1;
    }
    
    window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL |
        SDL_WINDOW_SHOWN);

    if (!window) {
        cerr << "cannot open window" << endl;
        return 1;
    }
    
    gl_context = SDL_GL_CreateContext(window);

    if (!gl_context) {
        cerr << "cannot create gl context" << endl;
        return 1;
    }

    if (glewInit() != GLEW_OK) {
        cerr << "failed to call glewInit" << endl;
        return 1;
    }

    cout << "window: " << window << endl
         << "gl_context: " << gl_context << endl;

    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();

	return 0;

}
