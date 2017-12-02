#ifndef WOLF3D_H
# define WOLF3D_H
# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <stdbool.h>

typedef struct  s_infos{
    SDL_Window  *window;
    SDL_Surface *surface;
    SDL_Event   event;
    bool        continuer;
    bool        isPressed;
}               t_infos;

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixelColor);

#endif
