/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphiclib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:35:16 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/01 16:48:27 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	setpixel3bpp(Uint8 *p, Uint32 pixelcolor)
{
	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
		p[0] = (pixelcolor >> 16) & 0xff;
		p[1] = (pixelcolor >> 8) & 0xff;
		p[2] = pixelcolor & 0xff;
	}
	else
	{
		p[0] = pixelcolor & 0xff;
		p[1] = (pixelcolor >> 8) & 0xff;
		p[2] = (pixelcolor >> 16) & 0xff;
	}
}

void	setpixel(SDL_Surface *surface, int x, int y, Uint32 pixelcolor)
{
	int		bytes_per_pixel;
	Uint8	*p;

	bytes_per_pixel = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bytes_per_pixel;
	if (bytes_per_pixel == 1)
		*p = pixelcolor;
	else if (bytes_per_pixel == 2)
		*(Uint16 *)p = pixelcolor;
	else if (bytes_per_pixel == 3)
		setpixel3bpp(p, pixelcolor);
	else if (bytes_per_pixel == 4)
		*(Uint32 *)p = pixelcolor;
}

void	redraw_the_line(SDL_Surface *surface, int pt1[2], int pt2[2],\
			Uint32 color)
{
	double	x;
	double	y;
	double	a;
	double	b;
	double	y_max;

	y = nearbyint(fmin((double)(pt1[1]), (double)(pt2[1])));
	y_max = nearbyint(fmax((double)(pt1[1]), (double)(pt2[1])));
	if (pt1[1] != pt2[1])
	{
		a = ((double)(pt2[0] - pt1[0]) / (double)(pt2[1] - pt1[1]));
		b = (double)(pt1[0]) - ((double)(pt1[1]) * a);
		while (y <= y_max)
		{
			x = nearbyint(a * y + b);
			setpixel(surface, (int)x, (int)y, color);
			y++;
		}
	}
}

void	draw_a_line(SDL_Surface *surface, int cor1[2], int cor2[2],\
			Uint32 color)
{
	double	x;
	double	y;
	double	a;
	double	b;
	int		x_max;

	x = nearbyint(fmin((double)(cor1[0]), (double)(cor2[0])));
	x_max = nearbyint(fmax((double)(cor1[0]), (double)(cor2[0])));
	if (cor1[0] != cor2[0])
	{
		a = ((double)(cor2[1] - cor1[1]) / (double)(cor2[0] - cor1[0]));
		b = (double)(cor1[1]) - ((double)cor1[0] * a);
		while (x <= x_max)
		{
			y = nearbyint(a * x + b);
			setpixel(surface, (int)x, (int)y, color);
			x++;
		}
	}
	redraw_the_line(surface, cor1, cor2, color);
}
