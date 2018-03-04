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

void	dothemove(t_dbl_point *pos, double vecx, double vecy)
{
	pos->x += vecx * 0.05;
	pos->y += vecy * 0.05;
}

void	moveplayer(t_infos *infos)
{
	t_dbl_point new_pos;

	new_pos.x = infos->player_pos.x;
	new_pos.y = infos->player_pos.y;
	if (infos->keypressed[UP])
		dothemove(&new_pos, infos->view_vector.x, infos->view_vector.y);
	if (infos->keypressed[DOWN])
		dothemove(&new_pos, -infos->view_vector.x, -infos->view_vector.y);
	if (infos->keypressed[LEFT])
		dothemove(&new_pos, infos->view_vector.y, -infos->view_vector.x);
	if (infos->keypressed[RIGHT])
		dothemove(&new_pos, -infos->view_vector.y, infos->view_vector.x);
	if (new_pos.x + new_pos.y >= 0 && (int)new_pos.x + (int)new_pos.y <= \
		infos->map_size.x + infos->map_size.y - 1 &&
		infos->world_map[(int)floor(new_pos.x)][(int)floor(new_pos.y)] == 0)
	{
		infos->player_pos.x = new_pos.x;
		infos->player_pos.y = new_pos.y;
	}
}
