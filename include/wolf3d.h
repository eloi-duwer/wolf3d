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

typedef struct	s_point {
	double		x;
	double		y;
}				t_dbl_point;

typedef struct	s_int_point {
	int			x;
	int			y;
}				t_int_point;

typedef struct	s_intersec {
	t_dbl_point	intersec_point;
	t_int_point	intersec_map;
	double		real_distance;
	double		projected_distance;
	t_dbl_point	view_vector;
	t_dbl_point	straight_view_vector;
}				t_intersec;

typedef struct	s_infos {
	SDL_Window	*window;
	SDL_Surface	*surface;
	SDL_Event	event;
	char		*file_name;
	int			**world_map;
	t_int_point	map_size;
	t_int_point	miniapsizepixels;
	t_int_point	minimaptopleftpos;
	int			pixelperblock;
	t_dbl_point	player_pos;
	t_dbl_point	view_vector;
	Uint32		color_to_put;
	int			keypressed[4];
	Uint32		lasttick;
	Uint32		elapsedtime;
	t_dbl_point	screenleftpos;
	t_dbl_point	pixelvector;
	t_intersec	intersection;
}				t_infos;

void			setpixel(SDL_Surface *surface, int x, int y, \
					Uint32 pixelcolor);
void			draw_a_line(SDL_Surface *surface, t_int_point cor1, \
					t_int_point cor2, Uint32 color);
void			quit_prog(t_infos *infos);
void			test_event(t_infos *infos);
void			main_loop(t_infos *infos);
void			printerror(t_infos *infos, char *message);
void			parsefile(t_infos *infos, char *file_name);
int				getsizeandpos(t_infos *infos, char *line);
void			allocatetheworldmap(t_infos *infos);
void			filloneline(int **map, int col, char *line, t_infos *infos);
void			init_struct(t_infos *infos, int carg, char **argnames);
void			drawminimap(t_infos *infos);
void			drawsquare(t_infos *infos, double x, double y);
void			handlekeyboardup(t_infos *infos);
void			handlekeyboarddown(t_infos *infos);
void			moveplayer(t_infos *infos);
void			rotateviewvector(t_dbl_point *viewvector, double angle);
void			mainrender(t_infos *infos);
void			normlizevector(t_dbl_point vector, t_dbl_point *res);
double			get_t_x(t_infos *infos, t_dbl_point vector, t_dbl_point *res);
double			get_t_y(t_infos *infos, t_dbl_point vector, t_dbl_point *res);
double			get_t_x_and_y(t_infos *infos, t_dbl_point vector, \
					t_int_point *res);
void			setminimaptopleft(t_infos *infos);
void			draw_vec(t_infos *infos, t_dbl_point vec, Uint32 color);
void			convert_map_pos_to_minimap_pos(t_infos *infos, \
					t_dbl_point pos, t_int_point *res);

#endif
