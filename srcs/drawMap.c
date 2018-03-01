#include <wolf3d.h>

void	convert_map_pos_to_minimap_pos(t_infos *infos, double *pos, int *res)
{
	res[0] = (int)((double)(infos->miniMapTopLeftPos[0]) + \
		pos[1] * (double)(infos->pixelPerBlock)) - 1;
	res[1] = (int)((double)(infos->miniMapTopLeftPos[1]) + \
		pos[0] * (double)(infos->pixelPerBlock)) - 1;
}

void	drawSquare(t_infos *infos, double x, double y)
{
	int 	i;
	double	pos_to_add;
	double	tmp_pos[2];
	int 	beginPoint[2];
	int 	endPoint[2];

	i = -1;
	pos_to_add = 1 / (double)(infos->pixelPerBlock);
	tmp_pos[0] = x;
	tmp_pos[1] = y;
	convert_map_pos_to_minimap_pos(infos, tmp_pos, beginPoint);
	tmp_pos[1] = y + 1;
	convert_map_pos_to_minimap_pos(infos, tmp_pos, endPoint);
	while (++i < infos->pixelPerBlock)
	{
		draw_a_line(infos->surface, beginPoint, endPoint, infos->color_to_put);
		++(beginPoint[1]);
		++(endPoint[1]);
	}
}

void	drawMiniMap(t_infos *infos)
{
	int 		i;
	int 		j;
	int			player_pos[2];

	i = -1;
	infos->color_to_put = SDL_MapRGB(infos->surface->format,\
		(Uint8)255, (Uint8)255, (Uint8)255);
	while (++i < infos->map_size[1])
	{
		j = -1;
		while (++j < infos->map_size[0])
		{
			if (infos->world_map[i][j] == 1)
				drawSquare(infos, (double)i, (double)j);
		}
	}
	convert_map_pos_to_minimap_pos(infos, infos->player_pos, player_pos);
	setPixel(infos->surface, player_pos[0], player_pos[1], infos->color_to_put);
}

void	setMinimapTopLeft(t_infos *infos)
{
	infos->miniMapTopLeftPos[0] = infos->surface->w - \
		(infos->pixelPerBlock * infos->map_size[0]);
	infos->miniMapTopLeftPos[1] = infos->surface->h - \
		(infos->pixelPerBlock * infos->map_size[1]);
}
