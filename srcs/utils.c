/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:14:08 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/18 17:51:59 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		test_x_y(int x, int y, t_int_point mapsize, int **map)
{
	if (x < 0 || y < 0 || x >= mapsize.x || y >= mapsize.y)
		return (-1);
	if (map[x][y] == 0)
		return (1);
	return (0);
}

void	quit_prog(t_infos *infos)
{
	SDL_DestroyWindow(infos->window);
	SDL_FreeSurface(infos->walls[0]);
	SDL_FreeSurface(infos->walls[1]);
	SDL_FreeSurface(infos->walls[2]);
	SDL_FreeSurface(infos->walls[3]);
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void	printerror(t_infos *infos, char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	quit_prog(infos);
}

void	init_struct(t_infos *infos, int carg, char **argnames)
{
	infos->window = NULL;
	infos->walls[0] = NULL;
	infos->walls[1] = NULL;
	infos->walls[2] = NULL;
	infos->walls[3] = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printerror(infos, "SDL_Init returned < 0");
	infos->window = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED,\
					SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	infos->surface = SDL_GetWindowSurface(infos->window);
	infos->miniapsizepixels.x = 300;
	infos->miniapsizepixels.y = 300;
	SDL_SetRelativeMouseMode(true);
	infos->color_to_put = SDL_MapRGB(infos->surface->format,\
		255, 255, 255);
	infos->file_name = (carg == 2 ? argnames[1] : "./map/test1.map");
	infos->keypressed[UP] = 0;
	infos->keypressed[DOWN] = 0;
	infos->keypressed[LEFT] = 0;
	infos->keypressed[RIGHT] = 0;
	infos->view_vector.y = -1.0;
	infos->view_vector.x = 0.0;
	infos->print_walls = true;
}

Uint32	getpixel(SDL_Surface *surface, int x, int y)
{
	Uint8			*pixel;

	if (x < surface->w && y < surface->h)
	{
		pixel = (Uint8*)surface->pixels;
		pixel += ((Uint32)y * (Uint32)surface->pitch) + \
			((Uint32)x * surface->format->BytesPerPixel);
		return (*((Uint32*)pixel));
	}
	return (0);
}
