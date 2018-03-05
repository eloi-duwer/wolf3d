/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 12:55:23 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/05 14:06:31 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	draw_procedural_color(t_infos *infos, double t, \
			t_int_point begin_point, t_int_point end_point)
{
	double		mult;
	Uint8		col;

	mult = 1 / sqrt(t + 1);
	col = (int)(255. * mult);
	if (infos->wall_color == UP)
		infos->color_to_put = SDL_MapRGB(infos->surface->format, 0, col, 0);
	else if (infos->wall_color == DOWN)
		infos->color_to_put = SDL_MapRGB(infos->surface->format, 0, 0, col);
	else if (infos->wall_color == LEFT)
		infos->color_to_put = SDL_MapRGB(infos->surface->format, col, 0, 0);
	else
		infos->color_to_put = SDL_MapRGB(infos->surface->format, col, col, 0);
	draw_a_line(infos->surface, begin_point, end_point, infos->color_to_put);
}
