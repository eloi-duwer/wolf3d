#include <wolf3d.h>

bool test_event(t_infos *infos)
{
    switch((infos->event).type)
    {
        case SDL_KEYDOWN:
            printf("KEYDOWN event: %s is pressed\n",
                SDL_GetKeyName(infos->event.key.keysym.sym));
            if ((infos->event).key.keysym.sym == SDLK_ESCAPE)
                return (false);
            break;
        case SDL_QUIT:
            printf("Going to quit\n");
            return (false);
        case SDL_MOUSEMOTION:
            if (infos->isPressed == true)
                setPixel(infos->surface, infos->event.motion.x, infos->event.motion.y, SDL_MapRGB(infos->surface->format, (Uint8)255, (Uint8)255, (Uint8)255));
            return (true);
        case SDL_MOUSEBUTTONDOWN:
            if (infos->event.button.button == SDL_BUTTON_LEFT)
                infos->isPressed = true;
            return (true);
        case SDL_MOUSEBUTTONUP:
            if (infos->event.button.button == SDL_BUTTON_LEFT)
                infos->isPressed = false;
            return (true);
        default:
            return (true);
    }
    return (true);
}

int main(int argc, char** argv) {

    t_infos infos;
    infos.continuer = true;
    infos.isPressed = false;

    if (argc > 2 && argv != NULL)
    {

    }
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Quit();
        return (-1);
    }
    infos.window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN );
    infos.surface = SDL_GetWindowSurface(infos.window);
    while (infos.continuer) {
        while (SDL_PollEvent(&(infos.event)) && infos.continuer)
            {
                infos.continuer = test_event(&infos);
                SDL_UpdateWindowSurface(infos.window);
            }
    }
    SDL_DestroyWindow(infos.window);
    SDL_Quit();
    return (EXIT_SUCCESS);
}
