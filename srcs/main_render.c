/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:57:34 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/01 18:27:41 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	draw_wall(t_infos *infos, int i, double height)
{
	int	begin_point[2];
	int	end_point[2];

	begin_point[0] = i;
	end_point[0] = i;
	begin_point[1] = (int)fmax((((double)infos->surface->h - height) / 2), 0);
	end_point[1] = (int)fmin((((double)infos->surface->h + height) / 2), \
		infos->surface->h - 1);
	draw_a_line(infos->surface, begin_point, end_point, infos->color_to_put);
}

void	set_color(t_infos *infos, double *vector, double t)
{
	double	mult;
	Uint8	color;

	mult = 1 / sqrt(t + 1);
	color = (int)(255. * mult);
	infos->color_to_put = SDL_MapRGB(infos->surface->format, color, \
		color, color);
}

void	calcintersecanddraw(t_infos *infos, double *vector, int i)
{
	double	t;
	int		final_coords[2];
	double	height;

	t = get_t_x_and_y(infos, vector, final_coords);
	height = fmin(infos->surface->h, infos->surface->h / (t + 1));
	set_color(infos, vector, t);
	draw_wall(infos, i, height);
}

void	draw_vec(t_infos *infos, double *vec, Uint32 color)
{
	double	end_pt[2];
	int		res1[2];
	int		res2[2];

	end_pt[0] = infos->player_pos[0] + vec[0];
	end_pt[1] = infos->player_pos[1] + vec[1];
	convert_map_pos_to_minimap_pos(infos, infos->player_pos, res1);
	convert_map_pos_to_minimap_pos(infos, end_pt, res2);
	if (res1[0] > 0 && res1[0] < infos->surface->w && res1[1] > 0 && \
		res1[1] < infos->surface->h && res2[0] > 0 && \
		res2[0] < infos->surface->w && res2[1] > 0 && \
		res2[1] < infos->surface->h)
		draw_a_line(infos->surface, res1, res2, color);
}

void	mainrender(t_infos *infos)
{
	double	screen_mid_pos[2];
	double	point[2];
	double	normalized_view_vector[2];
	double	i;

	SDL_FillRect(infos->surface, NULL, SDL_MapRGB(infos->surface->format,\
		(Uint8)0, (Uint8)0, (Uint8)0));
	screen_mid_pos[0] = infos->player_pos[0] + infos->view_vector[0];
	screen_mid_pos[1] = infos->player_pos[1] + infos->view_vector[1];
	infos->screenleftpos[0] = screen_mid_pos[0] + -infos->view_vector[1];
	infos->screenleftpos[1] = screen_mid_pos[1] + infos->view_vector[0];
	infos->pixelvector[0] = ((screen_mid_pos[0] - infos->screenleftpos[0]) /\
		((double)infos->surface->w)) * 2;
	infos->pixelvector[1] = ((screen_mid_pos[1] - infos->screenleftpos[1]) /\
		((double)infos->surface->w)) * 2;
	i = -1;
	while (++i < (double)(infos->surface->w))
	{
		point[0] = infos->screenleftpos[0] + (infos->pixelvector[0] * i);
		point[1] = infos->screenleftpos[1] + (infos->pixelvector[1] * i);
		normalized_view_vector[0] = point[0] - infos->player_pos[0];
		normalized_view_vector[1] = point[1] - infos->player_pos[1];
		if (i == floor(infos->surface->w / 2))
		{
			draw_vec(infos, normalized_view_vector, \
				SDL_MapRGB(infos->surface->format, \
				(Uint8)255, (Uint8)255, (Uint8)255));
		}
		calcintersecanddraw(infos, normalized_view_vector, (int)i);
	}
}
