/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:57:34 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/05 14:04:40 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	calcintersecanddraw(t_infos *infos, t_dbl_point vector, int i)
{
	double		t;
	t_dbl_point	final_coords;
	double		height;
	t_int_point	begin_point;
	t_int_point	end_point;

	t = get_t_x_and_y(infos, vector, &final_coords);
	t = t * cos(infos->angle);
	height = nearbyint(infos->surface->h / t);
	begin_point.x = i;
	end_point.x = i;
	begin_point.y = (int)fmax((((double)infos->surface->h - height) / 2), 0);
	end_point.y = (int)fmin((((double)infos->surface->h + height) / 2), \
		infos->surface->h - 1);
	if (infos->print_walls == false)
		draw_procedural_color(infos, t, begin_point, end_point);
	else
		print_texture_line(infos, final_coords, begin_point, end_point, height);
	procedural_floor_roof(infos, begin_point, end_point);
}

void	draw_vec(t_infos *infos, t_dbl_point vec, Uint32 color)
{
	t_dbl_point	end_pt;
	t_int_point	res1;
	t_int_point	res2;

	end_pt.x = infos->player_pos.x + vec.x;
	end_pt.y = infos->player_pos.y + vec.y;
	convert_map_pos_to_minimap_pos(infos, infos->player_pos, &res1);
	convert_map_pos_to_minimap_pos(infos, end_pt, &res2);
	if (res1.x > 0 && res1.x < infos->surface->w && \
		res1.y > 0 && res1.y < infos->surface->h && \
		res2.x > 0 && res2.x < infos->surface->w && \
		res2.y > 0 && res2.y < infos->surface->h)
		draw_a_line(infos->surface, res1, res2, color);
}

void	init_values(t_infos *infos)
{
	t_dbl_point screen_mid_pos;

	ft_memset(infos->surface->pixels, 0, infos->surface->pitch \
		* infos->surface->h);
	screen_mid_pos.x = infos->player_pos.x + infos->view_vector.x;
	screen_mid_pos.y = infos->player_pos.y + infos->view_vector.y;
	infos->screenleftvec.x = screen_mid_pos.x + infos->view_vector.y - infos->player_pos.x;
	infos->screenleftvec.y = screen_mid_pos.y + -infos->view_vector.x - infos->player_pos.y;
}

void	mainrender(t_infos *infos)
{
	t_dbl_point	normalized_view_vector;
	double		i;
	double		unit_angle;

	init_values(infos);
	infos->angle = -M_PI / 4;
	normlizevector(infos->screenleftvec, &normalized_view_vector);
	unit_angle = (M_PI / 2) / infos->surface->w;
	i = -1;
	while (++i < (double)(infos->surface->w))
	{
		calcintersecanddraw(infos, normalized_view_vector, (int)i);
		rotateviewvector(&normalized_view_vector, unit_angle);
		infos->angle += unit_angle;
	}
}
