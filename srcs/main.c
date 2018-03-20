/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:53:45 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/18 17:16:23 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	test_event(t_infos *infos)
{
	int event_type;

	event_type = (infos->event).type;
	if (event_type == SDL_KEYDOWN)
		handlekeyboarddown(infos);
	else if (event_type == SDL_KEYUP)
		handlekeyboardup(infos);
	else if (event_type == SDL_QUIT)
		quit_prog(infos);
	else if (event_type == SDL_MOUSEMOTION)
	{
		rotateviewvector(&(infos->view_vector),\
				(double)(infos->event.motion.xrel) * 0.01);
	}
}

void	main_loop(t_infos *infos)
{
	Uint32	tick;

	while (true)
	{
		infos->lasttick = SDL_GetTicks();
		while (SDL_PollEvent(&(infos->event)))
			test_event(infos);
		moveplayer(infos);
		mainrender(infos);
		drawminimap(infos);
		SDL_UpdateWindowSurface(infos->window);
		tick = SDL_GetTicks();
		infos->elapsedtime = tick - infos->lasttick;
		infos->lasttick = tick;
	}
}

void	load_images(t_infos *infos)
{
	infos->walls[0] = SDL_LoadBMP("./img/stone_wall.bmp");
	infos->walls[1] = SDL_LoadBMP("./img/wooden_wall.bmp");
	infos->walls[2] = SDL_LoadBMP("./img/bricks_wall.bmp");
	infos->walls[3] = SDL_LoadBMP("./img/cinder_wall.bmp");
	if (infos->walls[0] == NULL || infos->walls[1] == NULL || \
		infos->walls[2] == NULL || infos->walls[3] == NULL)
		printerror(infos, "Une des quatre textures est invalide");
}

int		main(int argc, char **argv)
{
	t_infos infos;

	init_struct(&infos, argc, argv);
	parsefile(&infos, infos.file_name);
	load_images(&infos);
	main_loop(&infos);
	return (EXIT_SUCCESS);
}
