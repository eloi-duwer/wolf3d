/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t_x_y.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:20:48 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/05 13:58:24 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

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

void	set_begin_point(t_infos *inf, t_dbl_point vec, t_dbl_point *pt, \
			bool is_x)
{
	if (is_x)
	{
		if (vec.x > 0)
			pt->x = ceil(inf->player_pos.x);
		else
			pt->x = floor(inf->player_pos.x);
		if (vec.x > 0)
			pt->y = inf->player_pos.y + (pt->x - inf->player_pos.x) * vec.y;
		else
			pt->y = inf->player_pos.y - (pt->x - inf->player_pos.x) * vec.y;
	}
	else
	{
		if (vec.y > 0)
			pt->y = ceil(inf->player_pos.y);
		else
			pt->y = floor(inf->player_pos.y);
		if (vec.y > 0)
			pt->x = inf->player_pos.x + (pt->y - inf->player_pos.y) * vec.x;
		else
			pt->x = inf->player_pos.x - (pt->y - inf->player_pos.y) * vec.x;
	}
}

double	get_t_x(t_infos *infos, t_dbl_point base_vec, t_dbl_point *res)
{
	t_dbl_point	vec_one_unit;
	t_dbl_point	point;
	t_int_point map_point;

	set_vector(base_vec, &vec_one_unit, true);
	set_begin_point(infos, vec_one_unit, &point, true);
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
	res->x = point.x;
	res->y = point.y;
	return (sqrt(pow(res->x - infos->player_pos.x, 2) + \
		pow(res->y - infos->player_pos.y, 2)));
}

double	get_t_y(t_infos *infos, t_dbl_point base_vec, t_dbl_point *res)
{
	t_dbl_point	vec_one_unit;
	t_dbl_point	point;
	t_int_point map_point;

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
	res->x = point.x;
	res->y = point.y;
	return (sqrt(pow(res->x - infos->player_pos.x, 2) + \
		pow(res->y - infos->player_pos.y, 2)));
}

double	get_t_x_and_y(t_infos *infos, t_dbl_point vector, t_dbl_point *res)
{
	t_dbl_point	res1;
	t_dbl_point	res2;
	double		t1;
	double		t2;

	t1 = get_t_x(infos, vector, &res1);
	t2 = get_t_y(infos, vector, &res2);
	if (t1 < t2)
	{
		res->x = res1.x;
		res->y = res1.y;
		if (vector.x > 0)
			infos->wall_color = RIGHT;
		else
			infos->wall_color = LEFT;
		return (t1);
	}
	res->x = res2.x;
	res->y = res2.y;
	if (vector.y > 0)
		infos->wall_color = DOWN;
	else
		infos->wall_color = UP;
	return (t2);
}
