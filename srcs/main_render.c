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
	//height = fmin(infos->surface->h, infos->surface->h / (t));
	height = infos->surface->h / t;
	begin_point.x = i;
	end_point.x = i;
	//begin_point.y = (int)fmax((((double)infos->surface->h - height) / 2), 0);
	//end_point.y = (int)fmin((((double)infos->surface->h + height) / 2), \
	//	infos->surface->h - 1);
	begin_point.y = (infos->surface->h - height) / 2;
	end_point.y = (infos->surface->h + height) / 2;
	if (infos->print_walls == false)
		draw_procedural_color(infos, t, begin_point, end_point);
	else
		print_texture_line(infos, final_coords, begin_point, end_point);
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

void	init_values(t_infos *infos, t_dbl_point *screen_mid_pos)
{
	ft_memset(infos->surface->pixels, 0, infos->surface->pitch \
		* infos->surface->h);
	screen_mid_pos->x = infos->player_pos.x + infos->view_vector.x;
	screen_mid_pos->y = infos->player_pos.y + infos->view_vector.y;
	infos->screenleftpos.x = screen_mid_pos->x + infos->view_vector.y;
	infos->screenleftpos.y = screen_mid_pos->y + -infos->view_vector.x;
	infos->pixelvector.x = ((screen_mid_pos->x - infos->screenleftpos.x) /\
		((double)infos->surface->w)) * 2;
	infos->pixelvector.y = ((screen_mid_pos->y - infos->screenleftpos.y) /\
		((double)infos->surface->w)) * 2;
}

void	mainrender(t_infos *infos)
{
	t_dbl_point	screen_mid_pos;
	t_dbl_point	point;
	t_dbl_point	normalized_view_vector;
	double		i;

	init_values(infos, &screen_mid_pos);
	infos->angle = M_PI / 4;
	i = -1;
	while (++i < (double)(infos->surface->w))
	{
		point.x = infos->screenleftpos.x + (infos->pixelvector.x * i);
		point.y = infos->screenleftpos.y + (infos->pixelvector.y * i);
		normalized_view_vector.x = point.x - infos->player_pos.x;
		normalized_view_vector.y = point.y - infos->player_pos.y;
		draw_vec(infos, normalized_view_vector, \
			SDL_MapRGB(infos->surface->format, \
			(Uint8)255, (Uint8)0, (Uint8)255));
		calcintersecanddraw(infos, normalized_view_vector, (int)i);
		infos->angle -= (M_PI / 2) / infos->surface->w;
	}
}
