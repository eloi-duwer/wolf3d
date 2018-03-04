/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:06:42 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/01 18:27:12 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	convert_map_pos_to_minimap_pos(t_infos *infos, t_dbl_point pos, \
			t_int_point *res)
{
	res->x = (int)((double)(infos->minimaptopleftpos.x) + \
		pos.x * (double)(infos->pixelperblock)) - 1;
	res->y = (int)((double)(infos->minimaptopleftpos.y) + \
		pos.y * (double)(infos->pixelperblock)) - 1;
}

void	drawsquare(t_infos *infos, double x, double y)
{
	int			i;
	t_dbl_point	tmp_pos;
	t_int_point	beginpoint;
	t_int_point	endpoint;

	i = -1;
	tmp_pos.x = x;
	tmp_pos.y = y;
	convert_map_pos_to_minimap_pos(infos, tmp_pos, &beginpoint);
	tmp_pos.y = y + 1;
	convert_map_pos_to_minimap_pos(infos, tmp_pos, &endpoint);
	while (++i < infos->pixelperblock)
	{
		draw_a_line(infos->surface, beginpoint, endpoint, infos->color_to_put);
		++(beginpoint.x);
		++(endpoint.x);
	}
}

void	drawminimap(t_infos *infos)
{
	int			i;
	int			j;
	t_int_point	player_pos;

	i = -1;
	infos->color_to_put = SDL_MapRGB(infos->surface->format, 255, 255, 255);
	while (++i < infos->map_size.x)
	{
		j = -1;
		while (++j < infos->map_size.y)
		{
			if (infos->world_map[i][j] == 1)
				drawsquare(infos, (double)i, (double)j);
		}
	}
	convert_map_pos_to_minimap_pos(infos, infos->player_pos, &player_pos);
	setpixel(infos->surface, player_pos.x, player_pos.y, infos->color_to_put);
}

void	setminimaptopleft(t_infos *infos)
{
	infos->minimaptopleftpos.x = infos->surface->w - \
		(infos->pixelperblock * infos->map_size.x);
	infos->minimaptopleftpos.y = infos->surface->h - \
		(infos->pixelperblock * infos->map_size.y);
}
