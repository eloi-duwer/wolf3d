/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 17:10:24 by eduwer            #+#    #+#             */
/*   Updated: 2018/03/01 17:10:26 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	rotateviewvector(t_dbl_point *viewvector, double angle)
{
	double temp;

	temp = viewvector->x;
	viewvector->x = viewvector->x * cos(angle) - viewvector->y * sin(angle);
	viewvector->y = temp * sin(angle) + viewvector->y * cos(angle);
}

void	normlizevector(t_dbl_point vector, t_dbl_point *res)
{
	double length;

	length = sqrt(vector.x * vector.x + vector.y * vector.y);
	res->x = vector.x / length;
	res->y = vector.y / length;
}
