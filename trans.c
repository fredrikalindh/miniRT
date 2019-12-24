/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 13:31:22 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/24 11:24:41 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void rot(double *a, double *b)
{
	double c;

	c = *a;
	*a = cos(0.1) * *a - sin(0.1) * *b;
	*b = sin(0.1) * c + cos(0.1) * *b;
}

void rotate(t_vector *dir, int key)
{
	if (key == 126)
		rot(&dir->z, &dir->y);
	else if (key == 123)
		rot(&dir->x, &dir->z);
	else if (key == 124)
		rot(&dir->z, &dir->x);
	else if (key == 125)
		rot(&dir->y, &dir->z);
	else if (key == 43)
		rot(&dir->y, &dir->x);
	else if (key == 47)
		rot(&dir->x, &dir->y);
	normalize(dir);
}

void move(t_vector *pos, t_vector *dir, int key)
{
	if (key == 13)
		op_addp(pos, g_rt.camera->dir);
	else if (key == 0)
		op_addp(pos, cross(g_rt.camera->dir, vector_xyz(0,1,0)));
	else if (key == 2)
		op_addp(pos, cross(vector_xyz(0,1,0), g_rt.camera->dir));
	else if (key == 1)
		op_addp(pos, op_mult_f(g_rt.camera->dir, -1));
	else if (key == 12)
		op_addp(pos, vector_xyz(0,-1,0));
	else if (key == 14)
		op_addp(pos, vector_xyz(0,1,0));
	else
		rotate(dir, key);
}
