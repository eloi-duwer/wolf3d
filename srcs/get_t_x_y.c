/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_x_y.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:20:48 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/01 18:24:57 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

int		test_x_y(int x, int y, int *mapsize, int **map)
{
	if (x < 0 || y < 0 || x >= mapsize[0] || y >= mapsize[1])
		return (-1);
	if (map[y][x] == 0)
		return (1);
	return (0);
}

void	set_vector(double *base_vector, double *res, bool is_x)
{
	double	coeff;

	if (is_x)
	{
		res[0] = ((base_vector[0] > 0) ? 1 : -1);
		coeff = res[0] / base_vector[0];
		res[1] = base_vector[1] * coeff;
	}
	else
	{
		res[1] = ((base_vector[1] > 0) ? 1 : -1);
		coeff = res[1] / base_vector[1];
		res[0] = base_vector[0] * coeff;
	}
}

double	get_t_x(t_infos *infos, double *tmp_vector, double *res)
{
	int		nearest_x;
	double	actual_y;
	int		y;
	double	vector[2];

	if (tmp_vector[1] == 0.0)
		return (666.66);
	set_vector(tmp_vector, vector, true);
	nearest_x = (vector[1] > 0 ? (int)ceil(infos->player_pos[1])\
		: (int)floor(infos->player_pos[1]));
	actual_y = infos->player_pos[0] + vector[0] * ((double)nearest_x - \
		infos->player_pos[1]) / vector[1];
	y = (int)floor(actual_y);
	while (test_x_y((vector[1] < 0 ? nearest_x - 1 : nearest_x), y, \
		infos->map_size, infos->world_map) == 1)
	{
		nearest_x += (int)vector[0];
		actual_y += vector[1];
		if ((int)floor(actual_y) != y)
			y = floor(actual_y);
	}
	if (nearest_x < 0 || y < 0 || \
		nearest_x >= infos->map_size[0] || y >= infos->map_size[1])
		return (666.66);
	res[0] = actual_y;
	res[1] = nearest_x;
	return (sqrt(pow(res[0] - infos->player_pos[0], 2) + pow(res[1] - \
		infos->player_pos[1], 2)));
}

double	get_t_y(t_infos *infos, double *tmp_vector, double *res)
{
	int		nearest_y;
	double	actual_x;
	int		x;
	double	vector[2];

	if (vector[0] == 0.0)
		return (666.66);
	set_vector(tmp_vector, vector, false);
	nearest_y = (vector[0] > 0 ? (int)ceil(infos->player_pos[0])\
		: (int)floor(infos->player_pos[0]));
	actual_x = infos->player_pos[1] + vector[1] * ((double)nearest_y - \
		infos->player_pos[0]) / vector[0];
	x = (int)floor(actual_x);
	while (test_x_y(x, (vector[0] < 0 ? nearest_y - 1 : nearest_y), \
		infos->map_size, infos->world_map) == 1)
	{
		nearest_y += (int)vector[1];
		actual_x += vector[0];
		if ((int)floor(actual_x) != x)
			x = floor(actual_x);
	}
	if (x < 0 || nearest_y < 0 || x >= infos->map_size[0] \
		|| nearest_y >= infos->map_size[1])
		return (666.66);
	res[0] = nearest_y;
	res[1] = actual_x;
	return (sqrt(pow(res[0] - infos->player_pos[0], 2) + pow(res[1] - \
		infos->player_pos[1], 2)));
}

double	get_t_x_and_y(t_infos *infos, double *vector, int *res)
{
	double	res1[2];
	double	res2[2];
	double	t1;
	double	t2;

	t1 = get_t_x(infos, vector, res1);
	t2 = get_t_y(infos, vector, res2);
	if (t1 < t2)
	{
		draw_vec(infos, res1, SDL_MapRGB(infos->surface->format, 255, 255, 0));
		return (t1);
	}
	draw_vec(infos, res2, SDL_MapRGB(infos->surface->format, 0, 255, 255));
	return (t2);
}
