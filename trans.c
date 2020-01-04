/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 13:31:22 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/04 16:38:35 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		trans(int key)
{
	if (g_rt.to_change.r != NULL && (key == PLUS || key == MIN))
	{
		*g_rt.to_change.r = (key == PLUS) ? *g_rt.to_change.r + 0.5 : *g_rt.to_change.r - 0.5;
		return (1);
	}
	if (g_rt.to_change.h != NULL && (key == H || key == B))
	{
		*g_rt.to_change.h = (key == H) ? *g_rt.to_change.h + 0.5 : *g_rt.to_change.h - 0.5;
		return (1);
	}
	return (0);
}

void rot(double *a, double *b)
{
	double c;

	c = *a;
	*a = cos(0.1) * *a - sin(0.1) * *b;
	*b = sin(0.1) * c + cos(0.1) * *b;
}

int rotate(t_vector *dir, int key)
{
	if (dir == NULL)
		return (0);
	if (key == UP)
		rot(&dir->y, &dir->z);
	else if (key == LEFT)
		rot(&dir->x, &dir->z);
	else if (key == RIGHT)
		rot(&dir->z, &dir->x);
	else if (key == DOWN)
		rot(&dir->z, &dir->y);
	else if (key == DOT)
		rot(&dir->y, &dir->x);
	else if (key == CMA)
		rot(&dir->x, &dir->y);
	normalize(dir);
	return (1);
}
//
// int rotate(t_vector *dir, int key)
// {
// 	if (dir == NULL)
// 		return (0);
// 	if ((key == UP && dir->z < 0) || (key == DOWN && dir->z > 0))
// 		rot(&dir->y, &dir->z);
// 	else if (key == LEFT)
// 		rot(&dir->x, &dir->z);
// 	else if (key == RIGHT)
// 		rot(&dir->z, &dir->x);
// 	else if ((key == DOWN && dir->z < 0) || (key == UP && dir->z > 0))
// 		rot(&dir->z, &dir->y);
// 	else if (key == DOT)
// 		rot(&dir->y, &dir->x);
// 	else if (key == CMA)
// 		rot(&dir->x, &dir->y);
// 	normalize(dir);
// 	return (1);
// }

int move(t_vector *pos, t_vector *dir, int key)
{
	if (pos == NULL)
		return (0);
	else if (key == W)
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
		return(rotate(dir, key));
	return (1);
}
