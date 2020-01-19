/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 13:31:22 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/19 13:32:45 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		rot(double *a, double *b)
{
	double	c;

	c = *a;
	*a = cos(0.1) * *a - sin(0.1) * *b;
	*b = sin(0.1) * c + cos(0.1) * *b;
}

static int	rotate(t_vector *dir, int key)
{
	if (dir == NULL)
		return (0);
	if (key == DOWN)
		rot(&dir->y, &dir->z);
	else if (key == LEFT)
		rot(&dir->x, &dir->z);
	else if (key == RIGHT)
		rot(&dir->z, &dir->x);
	else if (key == UP)
		rot(&dir->z, &dir->y);
	else if (key == DOT)
		rot(&dir->y, &dir->x);
	else if (key == CMA)
		rot(&dir->x, &dir->y);
	normalize(dir);
	return (1);
}

int			move(t_vector *pos, t_vector *dir, int key)
{
	if (pos == NULL)
		return (0);
	else if (key == W)
		op_addp(pos, g_rt.camera->dir);
	else if (key == D)
		op_addp(pos, g_rt.camera->right);
	else if (key == A)
		op_addp(pos, op_mult_f(g_rt.camera->right, -1));
	else if (key == S)
		op_addp(pos, op_mult_f(g_rt.camera->dir, -1));
	else if (key == E)
		op_addp(pos, cross(g_rt.camera->dir, g_rt.camera->right));
	else if (key == Q)
		op_addp(pos, cross(g_rt.camera->right, g_rt.camera->dir));
	else
		return (rotate(dir, key));
	return (1);
}

int			trans(int key)
{
	if (g_rt.select.r != NULL && (key == PLUS || key == MIN))
	{
		*g_rt.select.r = (key == PLUS) ?
		*g_rt.select.r + 0.5 : *g_rt.select.r - 0.5;
		*g_rt.select.r < 0 ? *g_rt.select.r = 0 : 0;
		return (1);
	}
	if (g_rt.select.h != NULL && (key == H || key == B))
	{
		*g_rt.select.h = (key == H) ?
		*g_rt.select.h + 0.5 : *g_rt.select.h - 0.5;
		*g_rt.select.h < 0 ? *g_rt.select.h = 0 : 0;
		return (1);
	}
	return (0);
}
