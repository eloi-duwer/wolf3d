#include <wolf3d.h>

void	handleKeyboardDown(t_infos *infos)
{
	switch ((infos->event).key.keysym.sym)
	{
		case SDLK_ESCAPE:
			quit_prog(infos);
		case SDLK_DOWN:
			infos->keyPressed[DOWN] = 1;
			break;
		case SDLK_UP:
			infos->keyPressed[UP] = 1;
			break;
		case SDLK_RIGHT:
			infos->keyPressed[RIGHT] = 1;
			break;
		case SDLK_LEFT:
			infos->keyPressed[LEFT] = 1;
			break;
	}
}

void	handleKeyboardUp(t_infos *infos)
{
	switch ((infos->event).key.keysym.sym)
	{
		case SDLK_ESCAPE:
			quit_prog(infos);
		case SDLK_DOWN:
			infos->keyPressed[DOWN] = 0;
			break;
		case SDLK_UP:
			infos->keyPressed[UP] = 0;
			break;
		case SDLK_RIGHT:
			infos->keyPressed[RIGHT] = 0;
			break;
		case SDLK_LEFT:
			infos->keyPressed[LEFT] = 0;
			break;
	}
}
