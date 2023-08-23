
//Using SDL and standard IO

#include <SDL.h>
#undef main

#include <SDL_syswm.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>
#include <string>

// Window Constants
const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 800;
const std::string WINDOW_NAME = "Project Sand";

SDL_Window* window = nullptr;
SDL_Surface* screen = nullptr;

GLuint VertexArrayID;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
    1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
};

int main(void)
{
    SDL_Init(0);
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    window = SDL_CreateWindow(WINDOW_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        screen = SDL_GetWindowSurface(window);

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x0f, 0x0f, 0x0f));

        SDL_UpdateWindowSurface(window);

        GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

        bool exit = false;
        SDL_Event event;
        while (!exit) {
            while (SDL_PollEvent(&event)) {

                switch (event.type) {
                case SDL_QUIT:
                    exit = true;
                    break;

                case SDL_WINDOWEVENT: {
                    const SDL_WindowEvent& wev = event.window;
                    switch (wev.event) {
                        case SDL_WINDOWEVENT_RESIZED:
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            break;

                        case SDL_WINDOWEVENT_CLOSE:
                            exit = true;
                            break;
                        }
                    } break;
                }
            }

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

            // Draw
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glDisableVertexAttribArray(0);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    window = nullptr;
    screen = nullptr;

    return 0;
}