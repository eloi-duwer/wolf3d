/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 13:02:25 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/18 15:29:34 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	print_texture_line(t_infos *infos, \
			t_int_point begin, t_int_point end, double height_px)
{
	t_int_point	pixel;
	SDL_Surface	*texture;
	int			total_height;
	Uint32		color;
	int			offscreen_pixels;

	texture = infos->walls[infos->wall_color];
	total_height = end.y - begin.y + 1;
	if (infos->wall_color == UP || infos->wall_color == DOWN)
		pixel.x = (int)(fmod(infos->final_coords.x, 1.) * texture->w);
	else
		pixel.x = (int)(fmod(infos->final_coords.y, 1.) * texture->w);
	offscreen_pixels = (height_px - (double)total_height) / 2.;
	while (begin.y <= end.y)
	{
		pixel.y = (int)((1. - ((double)(end.y - begin.y + offscreen_pixels) / \
			height_px)) * (double)texture->h);
		color = getpixel(texture, pixel.x, pixel.y);
		setpixel(infos->surface, begin.x, begin.y, color);
		++(begin.y);
	}
}
