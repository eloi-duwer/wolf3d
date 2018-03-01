/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameMechanics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:21:10 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/01 16:34:16 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	dothemove(double *pos, double vecx, double vecy)
{
	pos[0] += vecx * 0.05;
	pos[1] += vecy * 0.05;
}

void	moveplayer(t_infos *infos)
{
	double new_pos[2];

	new_pos[0] = infos->player_pos[0];
	new_pos[1] = infos->player_pos[1];
	if (infos->keypressed[UP])
		dothemove(new_pos, infos->view_vector[0], infos->view_vector[1]);
	if (infos->keypressed[DOWN])
		dothemove(new_pos, -infos->view_vector[0], -infos->view_vector[1]);
	if (infos->keypressed[LEFT])
		dothemove(new_pos, -infos->view_vector[1], infos->view_vector[0]);
	if (infos->keypressed[RIGHT])
		dothemove(new_pos, infos->view_vector[1], -infos->view_vector[0]);
	if (infos->world_map[(int)floor(new_pos[0])][(int)floor(new_pos[1])] == 0)
	{
		infos->player_pos[0] = new_pos[0];
		infos->player_pos[1] = new_pos[1];
	}
}
