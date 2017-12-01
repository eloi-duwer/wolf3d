#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}

bool test_event(SDL_Event *event, SDL_Surface *surface, bool *isPressed)
{
    switch((*event).type)
    {
        case SDL_KEYDOWN:
            printf("KEYDOWN event: %s is pressed\n",
                SDL_GetKeyName(event->key.keysym.sym));
            if ((*event).key.keysym.sym == SDLK_ESCAPE)
                return (false);
            break;
        case SDL_QUIT:
            printf("Going to quit\n");
            return (false);
        case SDL_MOUSEMOTION:
            if (*isPressed == true)
                setPixel(surface, event->motion.x, event->motion.y, SDL_MapRGB(surface->format, (Uint8)255, (Uint8)255, (Uint8)255));
            return (true);
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT)
                *isPressed = true;
            return (true);
        case SDL_MOUSEBUTTONUP:
            if (event->button.button == SDL_BUTTON_LEFT)
                *isPressed = false;
            return (true);
        default:
            return (true);
    }
}

int main(int argc, char** argv) {
    SDL_Window* window;
    SDL_Surface* screen;
    SDL_Event event;
    bool continuer = true;
    bool isPressed = false;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Quit();
        return -1;
    }
    window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN );
    screen = SDL_GetWindowSurface(window);
    while (continuer) {
        while (SDL_PollEvent(&event) && continuer)
            {
                continuer = test_event(&event, screen, &isPressed);
                SDL_UpdateWindowSurface(window);
            }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (EXIT_SUCCESS);
}
