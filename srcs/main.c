#include <wolf3d.h>

void 	test_event(t_infos *infos)
{
	switch((infos->event).type)
	{
		case SDL_KEYDOWN:
			handleKeyboardDown(infos);
			break;
		case SDL_KEYUP:
			handleKeyboardUp(infos);
			break;
		case SDL_QUIT:
			quit_prog(infos);
		case SDL_MOUSEMOTION:
			rotateViewVector(infos->view_vector,\
				(double)(infos->event.motion.xrel) * 0.01);
			break;
    }
}

void	main_loop(t_infos *infos)
{
	Uint32	tick;
	int		time_to_wait;

	while (true)
	{
		infos->lastTick = SDL_GetTicks();
		while (SDL_PollEvent(&(infos->event)))
			test_event(infos);
		movePlayer(infos);
		mainRender(infos);
		drawMiniMap(infos);
		SDL_UpdateWindowSurface(infos->window);
		tick = SDL_GetTicks();
		time_to_wait = (int)(1000 / 60) - (tick - infos->lastTick);
		infos->lastTick = tick;
		if (time_to_wait > 0)
			SDL_Delay((Uint32)time_to_wait);
	}
}

int 	main(int argc, char** argv)
{
	t_infos infos;

	init_struct(&infos, argc, argv);
	parseFile(&infos, infos.fileName);
	main_loop(&infos);
    return (EXIT_SUCCESS);
}
