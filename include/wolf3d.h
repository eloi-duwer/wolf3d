#ifndef WOLF3D_H
# define WOLF3D_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <stdbool.h>
# include <math.h>
# include <libft.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# define  UP 0
# define  DOWN 1
# define  LEFT 2
# define  RIGHT 3

typedef struct	s_intersec {
	double		intersec_point[2];
	int			intersec_map[2];
	double		real_distance;
	double		projected_distance;
	double		view_vector[2];
	double		straight_view_vector[2];
}				t_intersec;

typedef struct  s_infos {
	SDL_Window  *window;
    SDL_Surface *surface;
    SDL_Event   event;
    char		*fileName;
	int         **world_map;
	int			map_size[2];
	int			miniMapSizePixels[2];
	int			miniMapTopLeftPos[2];
	int			pixelPerBlock;
	double		player_pos[2];
	double		view_vector[2];
	Uint32		color_to_put;
	int			keyPressed[4];
	Uint32		lastTick;
	Uint32		elapsedTime;
	double		screenLeftPos[2];
	double		pixelVector[2];
	t_intersec	intersection;
}               t_infos;

void 			setPixel(SDL_Surface *surface, int x, int y, Uint32 pixelColor);
void			draw_a_line(SDL_Surface *surface, int cor1[2], int cor2[2],\
					Uint32 color);
void			quit_prog(t_infos *infos);
void 			test_event(t_infos *infos);
void			main_loop(t_infos *infos);
void			printError(t_infos *infos, char *message);
void			parseFile(t_infos *infos, char *fileName);
int				getSizeAndPos(t_infos *infos, char *line);
void			allocateTheWorldMap(t_infos *infos);
void			fillOneLine(int *mapLine, char *line, t_infos *infos);
void			init_struct(t_infos *infos, int carg, char **argNames);
void			drawMiniMap(t_infos *infos);
void			drawSquare(t_infos *infos, double x, double y);
void			handleKeyboardDown(t_infos *infos);
void			handleKeyboardUp(t_infos *infos);
void			movePlayer(t_infos *infos);
void			rotateViewVector(double *viewVector, double angle);
void			mainRender(t_infos *infos);
void			normalizeVector(double *vector, double *res);
double			get_t_x(t_infos *infos, double *vector, double *res);
double			get_t_y(t_infos *infos, double *vector, double *res);
double			get_t_x_and_y(t_infos *infos, double *vector, int *res);
void			setMinimapTopLeft(t_infos *infos);
void			draw_vec(t_infos *infos, double *vec, Uint32 color);
void			convert_map_pos_to_minimap_pos(t_infos *infos, double *pos, int *res);

#endif
