#include <wolf3d.h>

void	drawWall(t_infos *infos, int i, double height)
{
	int	begin_point[2];
	int	end_point[2];

	begin_point[0] = i;
	end_point[0] = i;
	begin_point[1] = (int)fmax((((double)infos->surface->h - height) / 2), 0);
	end_point[1] = (int)fmin((((double)infos->surface->h + height) / 2), infos->surface->h - 1);
	draw_a_line(infos->surface, begin_point, end_point, infos->color_to_put);
}

void	setColor(t_infos *infos, double *vector, double t)
{
	double 	mult;
	Uint8	color;

	mult = 1 / sqrt(t + 1);
	color = (int)(255. * mult);
	infos->color_to_put = SDL_MapRGB(infos->surface->format, color, color, color);
	/*if (vector[0] > 0 && vector[1] > 0)
		infos->color_to_put = SDL_MapRGB(infos->surface->format,\
			(Uint8)255, (Uint8)0, (Uint8)0);
	else if (vector[0] <= 0 && vector[1] > 0)
		infos->color_to_put = SDL_MapRGB(infos->surface->format,\
			(Uint8)0, (Uint8)255, (Uint8)0);
	else if (vector[0] <= 0 && vector[1] <= 0)
		infos->color_to_put = SDL_MapRGB(infos->surface->format,\
			(Uint8)0, (Uint8)0, (Uint8)255);
	else if (vector[0] > 0 && vector[1] <= 0)
		infos->color_to_put = SDL_MapRGB(infos->surface->format,\
			(Uint8)255, (Uint8)255, (Uint8)0);*/
}

void	calcIntersecAndDraw(t_infos *infos, double *vector, int i)
{
	double	t;
	int		final_coords[2];
	double	height;

	t = get_t_x_and_y(infos, vector, final_coords);
	height = fmin(infos->surface->h, infos->surface->h / (t + 1));
	setColor(infos, vector, t);
	drawWall(infos, i, height);
}

void	draw_vec(t_infos *infos, double *vec, Uint32 color)
{
	double end_pt[2];
	int res1[2];
	int res2[2];

	end_pt[0] = infos->player_pos[0] + vec[0];
	end_pt[1] = infos->player_pos[1] + vec[1];
	convert_map_pos_to_minimap_pos(infos, infos->player_pos, res1);
	convert_map_pos_to_minimap_pos(infos, end_pt, res2);
	if (res1[0] > 0 && res1[0] < infos->surface->w && res1[1] > 0 && res1[1] < infos->surface->h\
		&& res2[0] > 0 && res2[0] < infos->surface->w && res2[1] > 0 && res2[1] < infos->surface->h)
	draw_a_line(infos->surface, res1, res2, color);
}

void	mainRender(t_infos *infos)
{
    double	screenMidPos[2];
    double	point[2];
    double	normalizedViewVector[2];
    double	i;

    SDL_FillRect(infos->surface, NULL, SDL_MapRGB(infos->surface->format,\
		(Uint8)0, (Uint8)0, (Uint8)0));
    screenMidPos[0] = infos->player_pos[0] + infos->view_vector[0]/* * 0.01*/;
    screenMidPos[1] = infos->player_pos[1] + infos->view_vector[1] /* * 0.01*/;
    infos->screenLeftPos[0] = screenMidPos[0] + -infos->view_vector[1]/* * 0.01*/;
    infos->screenLeftPos[1] = screenMidPos[1] + infos->view_vector[0]/* * 0.01*/;
    infos->pixelVector[0] = ((screenMidPos[0] - infos->screenLeftPos[0]) /\
		((double)infos->surface->w)) * 2;
	infos->pixelVector[1] = ((screenMidPos[1] - infos->screenLeftPos[1]) /\
		((double)infos->surface->w)) * 2;
	i = -1;
	while (++i < (double)(infos->surface->w))
	{
		point[0] = infos->screenLeftPos[0] + (infos->pixelVector[0] * i);
		point[1] = infos->screenLeftPos[1] + (infos->pixelVector[1] * i);
		normalizedViewVector[0] = point[0] - infos->player_pos[0];
		normalizedViewVector[1] = point[1] - infos->player_pos[1];
		if (i == floor(infos->surface->w / 2))
		{
			draw_vec(infos, normalizedViewVector, SDL_MapRGB(infos->surface->format,\
			(Uint8)255, (Uint8)255, (Uint8)255));
		}
			calcIntersecAndDraw(infos, normalizedViewVector, (int)i);
	}
}
