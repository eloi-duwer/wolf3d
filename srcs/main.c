#include <wolf3d.h>

void	quit_prog(t_infos *infos)
{
	SDL_DestroyWindow(infos->window);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void printError(t_infos *infos, char *message)
{
	write(2, message, ft_strlen(message));
	quit_prog(infos);
}

void 	test_event(t_infos *infos)
{
	switch((infos->event).type)
	{
		case SDL_KEYDOWN:
			if ((infos->event).key.keysym.sym == SDLK_ESCAPE)
				quit_prog(infos);
			break;
		case SDL_QUIT:
			quit_prog(infos);
		case SDL_MOUSEMOTION:

			break;
        case SDL_MOUSEBUTTONDOWN:

            break;
        case SDL_MOUSEBUTTONUP:

			break;
    }
}

void	main_loop(t_infos *infos)
{
	while (true)
	{
		if (!SDL_WaitEvent(&(infos->event)))
			printError(infos, SDL_GetError());
		test_event(infos);
		SDL_UpdateWindowSurface(infos->window);
		while (SDL_PollEvent(&(infos->event)))
		{
			test_event(infos);
			SDL_UpdateWindowSurface(infos->window);
		}
	}
}

int 	main(int argc, char** argv) {
	t_infos infos;

	char *name;

	name = (argv[1] ? argv[1] : "./map/test1.map");
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Quit();
        return (-1);
    }
    infos.window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_SHOWN );
    infos.surface = SDL_GetWindowSurface(infos.window);
	parseFile(&infos, name);
    SDL_SetRelativeMouseMode(true);
	infos.color_to_put = SDL_MapRGB(infos.surface->format, (Uint8)255, (Uint8)255, (Uint8)255);
	main_loop(&infos);
    return (EXIT_SUCCESS);
}
