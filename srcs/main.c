/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:53:45 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/01 16:57:12 by eduwer           ###   ########.fr       */
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

int		main(int argc, char **argv)
{
	t_infos infos;

	init_struct(&infos, argc, argv);
	parsefile(&infos, infos.file_name);
	main_loop(&infos);
	return (EXIT_SUCCESS);
}
