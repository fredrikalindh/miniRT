/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 13:31:22 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/24 21:14:26 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	trans(int key)
{
	if (g_rt.to_change.r != NULL && (key == 27 || key == 44))
		*g_rt.to_change.r = (key == 27) ? *g_rt.to_change.r + 0.5 : *g_rt.to_change.r - 0.5;
	if (g_rt.to_change.h != NULL && (key == 27 || key == 44))
		*g_rt.to_change.h = (key == 27) ? *g_rt.to_change.h + 0.5 : *g_rt.to_change.h - 0.5;

}

void rot(double *a, double *b)
{
	double c;

	c = *a;
	*a = cos(0.1) * *a - sin(0.1) * *b;
	*b = sin(0.1) * c + cos(0.1) * *b;
}

void rotate(t_vector *dir, int key)
{
	if (dir == NULL)
		return ;
	if (key == UP)
		rot(&dir->z, &dir->y);
	else if (key == LEFT)
		rot(&dir->x, &dir->z);
	else if (key == RIGHT)
		rot(&dir->z, &dir->x);
	else if (key == DOWN)
		rot(&dir->y, &dir->z);
	else if (key == DOT)
		rot(&dir->y, &dir->x);
	else if (key == CMA)
		rot(&dir->x, &dir->y);
	normalize(dir);
}

void move(t_vector *pos, t_vector *dir, int key)
{
	if (pos == NULL)
		return ;
	if (key == W)
		op_addp(pos, g_rt.camera->dir);
	else if (key == A)
		op_addp(pos, cross(g_rt.camera->dir, vector_xyz(0,1,0)));
	else if (key == D)
		op_addp(pos, cross(vector_xyz(0,1,0), g_rt.camera->dir));
	else if (key == S)
		op_addp(pos, op_mult_f(g_rt.camera->dir, -1));
	else if (key == Q)
		op_addp(pos, vector_xyz(0,-1,0));
	else if (key == E)
		op_addp(pos, vector_xyz(0,1,0));
	else
		rotate(dir, key);
}
