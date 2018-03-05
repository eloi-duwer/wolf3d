/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:48:46 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/05 13:01:19 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	handlekeyboarddown(t_infos *infos)
{
	int key;

	key = (infos->event).key.keysym.sym;
	if (key == SDLK_ESCAPE)
		quit_prog(infos);
	else if (key == SDLK_DOWN)
		infos->keypressed[DOWN] = 1;
	else if (key == SDLK_UP)
		infos->keypressed[UP] = 1;
	else if (key == SDLK_RIGHT)
		infos->keypressed[RIGHT] = 1;
	else if (key == SDLK_LEFT)
		infos->keypressed[LEFT] = 1;
}

void	handlekeyboardup(t_infos *infos)
{
	int key;

	key = (infos->event).key.keysym.sym;
	if (key == SDLK_ESCAPE)
		quit_prog(infos);
	else if (key == SDLK_DOWN)
		infos->keypressed[DOWN] = 0;
	else if (key == SDLK_UP)
		infos->keypressed[UP] = 0;
	else if (key == SDLK_RIGHT)
		infos->keypressed[RIGHT] = 0;
	else if (key == SDLK_LEFT)
		infos->keypressed[LEFT] = 0;
	else if (key == SDLK_RETURN)
	{
		if (infos->print_walls == true)
			infos->print_walls = false;
		else
			infos->print_walls = true;
	}
}
