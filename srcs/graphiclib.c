#include <wolf3d.h>

void	setPixel3bpp(Uint8 *p, Uint32 pixelColor)
{
	if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
	{
		p[0] = (pixelColor >> 16) & 0xff;
		p[1] = (pixelColor >> 8) & 0xff;
		p[2] = pixelColor & 0xff;
	}
	else
	{
		p[0] = pixelColor & 0xff;
		p[1] = (pixelColor >> 8) & 0xff;
		p[2] = (pixelColor >> 16) & 0xff;
	}
}

void	setPixel(SDL_Surface *surface, int x, int y, Uint32 pixelColor)
{
    int 	bpp = surface->format->BytesPerPixel;
    Uint8	*p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
		case 1:
			*p = pixelColor;
			break;

		case 2:
			*(Uint16 *)p = pixelColor;
			break;

		case 3:
			setPixel3bpp(p, pixelColor);
			break;

		case 4:
			*(Uint32 *)p = pixelColor;
			break;
    }
}

void	redraw_the_line(SDL_Surface *surface, int pt1[2], int pt2[2],\
			Uint32 color)
{
	double 	x;
	double 	y;
	double 	a;
	double 	b;
	double 	y_max;

	y = nearbyint(fmin((double)(pt1[1]), (double)(pt2[1])));
	y_max = nearbyint(fmax((double)(pt1[1]), (double)(pt2[1])));
	if (pt1[1] != pt2[1])
	{
		a = ((double)(pt2[0] - pt1[0]) / (double)(pt2[1] - pt1[1]));
		b = (double)(pt1[0]) - ((double)(pt1[1]) * a);
		while (y <= y_max)
		{
			x = nearbyint(a * y + b);
			setPixel(surface, (int)x, (int)y, color);
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
			setPixel(surface, (int)x, (int)y, color);
			x++;
		}
	}
	redraw_the_line(surface, cor1, cor2, color);
}
