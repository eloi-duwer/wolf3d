#include <wolf3d.h>

void	quit_prog(t_infos *infos)
{
	SDL_DestroyWindow(infos->window);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void	printError(t_infos *infos, char *message)
{
	write(2, message, ft_strlen(message));
	quit_prog(infos);
}

void	init_struct(t_infos *infos, int carg, char **argNames)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
        printError(infos, "SDL_Init returned < 0");
    infos->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED,\
					SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN );
    infos->surface = SDL_GetWindowSurface(infos->window);
    infos->miniMapSizePixels[0] = 300;
    infos->miniMapSizePixels[1] = 300;
	SDL_SetRelativeMouseMode(true);
	infos->color_to_put = SDL_MapRGB(infos->surface->format,\
		(Uint8)255, (Uint8)255, (Uint8)255);
	infos->fileName = (carg == 2 ? argNames[1] : "./map/test1.map");
	infos->keyPressed[UP] = 0;
	infos->keyPressed[DOWN] = 0;
	infos->keyPressed[LEFT] = 0;
	infos->keyPressed[RIGHT] = 0;
	infos->view_vector[0] = -1.0;
	infos->view_vector[1] = 0.0;
}
