/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 15:07:21 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/01 16:23:30 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3

typedef struct	s_intersec {
	double		intersec_point[2];
	int			intersec_map[2];
	double		real_distance;
	double		projected_distance;
	double		view_vector[2];
	double		straight_view_vector[2];
}				t_intersec;

typedef struct	s_infos {
	SDL_Window	*window;
	SDL_Surface	*surface;
	SDL_Event	event;
	char		*file_name;
	int			**world_map;
	int			map_size[2];
	int			miniapsizepixels[2];
	int			minimaptopleftpos[2];
	int			pixelperblock;
	double		player_pos[2];
	double		view_vector[2];
	Uint32		color_to_put;
	int			keypressed[4];
	Uint32		lattick;
	Uint32		elapsedtime;
	double		screenleftpos[2];
	double		pixelvector[2];
	t_intersec	intersection;
}				t_infos;

void			setpixel(SDL_Surface *surface, int x, int y, \
					Uint32 pixelcolor);
void			draw_a_line(SDL_Surface *surface, int cor1[2], int cor2[2],\
					Uint32 color);
void			quit_prog(t_infos *infos);
void			test_event(t_infos *infos);
void			main_loop(t_infos *infos);
void			printerror(t_infos *infos, char *message);
void			parsefile(t_infos *infos, char *file_name);
int				getsizeandpos(t_infos *infos, char *line);
void			allocatetheworldmap(t_infos *infos);
void			filloneline(int *mapline, char *line, t_infos *infos);
void			init_struct(t_infos *infos, int carg, char **argnames);
void			drawminimap(t_infos *infos);
void			drawsquare(t_infos *infos, double x, double y);
void			handlekeyboardup(t_infos *infos);
void			handlekeyboarddown(t_infos *infos);
void			moveplayer(t_infos *infos);
void			rotateviewvector(double *viewvector, double angle);
void			mainrender(t_infos *infos);
void			normlizevector(double *vector, double *res);
double			get_t_x(t_infos *infos, double *vector, double *res);
double			get_t_y(t_infos *infos, double *vector, double *res);
double			get_t_x_and_y(t_infos *infos, double *vector, int *res);
void			setminimaptopleft(t_infos *infos);
void			draw_vec(t_infos *infos, double *vec, Uint32 color);
void			convert_map_pos_to_minimap_pos(t_infos *infos, double *pos, \
					int *res);

#endif
