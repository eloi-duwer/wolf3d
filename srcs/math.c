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

void	rotateviewvector(double *viewvector, double angle)
{
	double temp;

	temp = viewvector[1];
	viewvector[1] = viewvector[1] * cos(angle) - viewvector[0] * sin(angle);
	viewvector[0] = temp * sin(angle) + viewvector[0] * cos(angle);
}

void	normlizevector(double *vector, double *res)
{
	double length;

	length = sqrt(vector[0] * vector[0] + vector[1] * vector[1]);
	res[0] = vector[0] / length;
	res[1] = vector[1] / length;
}
