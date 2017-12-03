#ifndef WOLF3D_H
# define WOLF3D_H
# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <stdbool.h>
# include <math.h>
# include <libft.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct  s_infos{
	SDL_Window  *window;
    SDL_Surface *surface;
    SDL_Event   event;
	int         **world_map;
	double		player_pos[2];
	double		view_vector[2];
	Uint32		color_to_put;
}               t_infos;

void 			setPixel(SDL_Surface *surface, int x, int y, Uint32 pixelColor);
void			draw_a_line(t_infos *infos, int cor1[2], int cor2[2]);
void			quit_prog(t_infos *infos);
void 			test_event(t_infos *infos);
void			main_loop(t_infos *infos);
void			printError(t_infos *infos, char *message);
void			parseFile(t_infos *infos, char *fileName);

#endif
