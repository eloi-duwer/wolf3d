/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_x_y.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:20:48 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/01 20:45:01 by eduwer           ###   ########.fr       */
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

/*
**	Le vecteur change dans res sera le veteur utilise pour avancer d'une case
**	a chaque etape.
*/

void	set_vector(t_dbl_point base_vector, t_dbl_point *res, bool is_x)
{
	double	coeff;

	if (is_x)
	{
		res->x = ((base_vector.x > 0) ? 1 : -1);
		coeff = res->x / base_vector.x;
		res->y = base_vector.y * coeff;
	}
	else
	{
		res->y = ((base_vector.y > 0) ? 1 : -1);
		coeff = res->y / base_vector.y;
		res->x = base_vector.x * coeff;
	}
}
/*
double	get_t_x(t_infos *infos, t_dbl_point tmp_vector, t_dbl_point *res)
{
	int			nearest_y;
	double		actual_x;
	int			x;
	t_dbl_point	vector;

	if (tmp_vector.x == 0.0)
		return (666.66);
	set_vector(tmp_vector, &vector, false);
	nearest_y = (vector.x > 0 ? (int)ceil(infos->player_pos.x)\
		: (int)floor(infos->player_pos.x));
	actual_x = infos->player_pos.y + vector.y * ((double)nearest_y - \
		infos->player_pos.x) / vector.x;
	x = (int)floor(actual_x);
	while (test_x_y(x, (vector.x < 0 ? nearest_y - 1 : nearest_y), \
		infos->map_size, infos->world_map) == 1)
	{
		nearest_y += (int)vector.y;
		actual_x += vector.x;
		if ((int)floor(actual_x) != x)
			x = floor(actual_x);
	}
	if (x < 0 || nearest_y < 0 || x >= infos->map_size.x \
		|| nearest_y >= infos->map_size.y)
		return (666.66);
	res->x = nearest_y - infos->player_pos.x;
	res->y = actual_x - infos->player_pos.y;
	return (sqrt(pow(res->x, 2) + pow(res->y, 2)));
}
*/
/*double	get_t_y(t_infos *infos, t_dbl_point tmp_vector, t_dbl_point *res)
{
	int			nearest_x;
	double		actual_y;
	int			y;
	t_dbl_point	vector;

	if (tmp_vector.y == 0.0)
		return (666.66);
	set_vector(tmp_vector, &vector, true);
	nearest_x = (vector.y > 0 ? (int)ceil(infos->player_pos.y)\
		: (int)floor(infos->player_pos.y));
	actual_y = infos->player_pos.x + vector.x * ((double)nearest_x - \
		infos->player_pos.y) / vector.y;
	y = (int)floor(actual_y);
	while (test_x_y((vector.y < 0 ? nearest_x - 1 : nearest_x), y, \
		infos->map_size, infos->world_map) == 1)
	{
		nearest_x += (int)vector.x;
		actual_y += vector.y;
		if ((int)floor(actual_y) != y)
			y = floor(actual_y);
	}
	if (nearest_x < 0 || y < 0 || \
		nearest_x >= infos->map_size.x || y >= infos->map_size.y)
		return (666.66);
	res->x = actual_y - infos->player_pos.x;
	res->y = nearest_x - infos->player_pos.y;
	return (sqrt(pow(res->x, 2) + pow(res->y, 2)));
}*/
void	set_begin_point(t_infos *inf, t_dbl_point vec, t_dbl_point *point, bool is_x)
{
	if (is_x)
	{
		if (vec.x > 0)
			point->x = ceil(inf->player_pos.x);
		else
			point->x = floor(inf->player_pos.x);
		if (vec.x > 0)
			point->y = inf->player_pos.y + (point->x - inf->player_pos.x) * vec.y;
		else
			point->y = inf->player_pos.y - (point->x - inf->player_pos.x) * vec.y;
	}
	else
	{
		if (vec.y > 0)
			point->y = ceil(inf->player_pos.y);
		else
			point->y = floor(inf->player_pos.y);
		if (vec.y > 0)
			point->x = inf->player_pos.x + (point->y - inf->player_pos.y) * vec.x;
		else
			point->x = inf->player_pos.x - (point->y - inf->player_pos.y) * vec.x;
	}
}

double get_t_x(t_infos *infos, t_dbl_point base_vec, t_dbl_point *res)
{
	t_dbl_point	vec_one_unit;
	t_dbl_point	point;
	t_int_point map_point;
	t_dbl_point	player_pos = infos->player_pos;

	if (base_vec.y == 0)
		return (666.66);
	set_vector(base_vec, &vec_one_unit, true);
	set_begin_point(infos, vec_one_unit, &point, true);
	/*point.x = (vec_one_unit.x > 0 ? ceil(infos->player_pos.x) : \
		floor(infos->player_pos.x));
	point.y = infos->player_pos.y + (point.x - infos->player_pos.x) \
		* vec_one_unit.y;*/
	map_point.y = (int)floor(point.y);
	map_point.x = (vec_one_unit.x > 0 ? (int)nearbyint(point.x) : \
		(int)floor(point.x - 0.1));
	while (test_x_y(map_point.x, map_point.y, infos->map_size, \
		infos->world_map) == 1)
	{
		point.x += vec_one_unit.x;
		point.y += vec_one_unit.y;
		map_point.y = (int)floor(point.y);
		map_point.x = (vec_one_unit.x > 0 ? (int)nearbyint(point.x) : \
			(int)floor(point.x - 0.1));
	}
	if (map_point.x < 0 || map_point.y < 0 || \
		map_point.x >= infos->map_size.x || map_point.y >= infos->map_size.y)
		return (666.66);
	res->x = point.x - infos->player_pos.x;
	res->y = point.y - infos->player_pos.y;
	return (sqrt(pow(res->x, 2) + pow(res->y, 2)));
}


double	get_t_y(t_infos *infos, t_dbl_point base_vec, t_dbl_point *res)
{
	t_dbl_point	vec_one_unit;
	t_dbl_point	point;
	t_int_point map_point;
	t_dbl_point	player_pos = infos->player_pos;

	if (base_vec.x == 0)
		return (666.66);
	set_vector(base_vec, &vec_one_unit, false);
	set_begin_point(infos, vec_one_unit, &point, false);
	map_point.x = (int)floor(point.x);
	map_point.y = (vec_one_unit.y > 0 ? (int)nearbyint(point.y) : \
		(int)floor(point.y - 0.1));
	while (test_x_y(map_point.x, map_point.y, infos->map_size, \
		infos->world_map) == 1)
	{
		point.x += vec_one_unit.x;
		point.y += vec_one_unit.y;
		map_point.x = (int)floor(point.x);
		map_point.y = (vec_one_unit.y > 0 ? (int)nearbyint(point.y) : \
			(int)floor(point.y - 0.1));
	}
	if (map_point.x < 0 || map_point.y < 0 || \
		map_point.x >= infos->map_size.x || map_point.y >= infos->map_size.y)
		return (666.66);
	res->x = point.x - infos->player_pos.x;
	res->y = point.y - infos->player_pos.y;
	return (sqrt(pow(res->x, 2) + pow(res->y, 2)));
}

double	get_t_x_and_y(t_infos *infos, t_dbl_point vector, t_int_point *res)
{
	t_dbl_point	res1;
	t_dbl_point	res2;
	double	t1;
	double	t2;

	t1 = get_t_x(infos, vector, &res1);
	t2 = get_t_y(infos, vector, &res2);
	if (t1 < t2)
		return (t1);
	return (t2);
}
