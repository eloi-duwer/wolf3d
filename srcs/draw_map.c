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

void	convert_map_pos_to_minimap_pos(t_infos *infos, double *pos, int *res)
{
	res[0] = (int)((double)(infos->minimaptopleftpos[0]) + \
		pos[1] * (double)(infos->pixelperblock)) - 1;
	res[1] = (int)((double)(infos->minimaptopleftpos[1]) + \
		pos[0] * (double)(infos->pixelperblock)) - 1;
}

void	drawsquare(t_infos *infos, double x, double y)
{
	int		i;
	double	pos_to_add;
	double	tmp_pos[2];
	int		beginpoint[2];
	int		endpoint[2];

	i = -1;
	pos_to_add = 1 / (double)(infos->pixelperblock);
	tmp_pos[0] = x;
	tmp_pos[1] = y;
	convert_map_pos_to_minimap_pos(infos, tmp_pos, beginpoint);
	tmp_pos[1] = y + 1;
	convert_map_pos_to_minimap_pos(infos, tmp_pos, endpoint);
	while (++i < infos->pixelperblock)
	{
		draw_a_line(infos->surface, beginpoint, endpoint, infos->color_to_put);
		++(beginpoint[1]);
		++(endpoint[1]);
	}
}

void	drawminimap(t_infos *infos)
{
	int			i;
	int			j;
	int			player_pos[2];

	i = -1;
	infos->color_to_put = SDL_MapRGB(infos->surface->format, 255, 255, 255);
	while (++i < infos->map_size[1])
	{
		j = -1;
		while (++j < infos->map_size[0])
		{
			if (infos->world_map[i][j] == 1)
				drawsquare(infos, (double)i, (double)j);
		}
	}
	convert_map_pos_to_minimap_pos(infos, infos->player_pos, player_pos);
	setpixel(infos->surface, player_pos[0], player_pos[1], infos->color_to_put);
}

void	setminimaptopleft(t_infos *infos)
{
	infos->minimaptopleftpos[0] = infos->surface->w - \
		(infos->pixelperblock * infos->map_size[0]);
	infos->minimaptopleftpos[1] = infos->surface->h - \
		(infos->pixelperblock * infos->map_size[1]);
}
