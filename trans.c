/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/23 13:31:22 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/23 17:24:44 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


void rotate(t_vector *dir, int key)
{
	if (key == 126)
		op_addp(dir, vector_xyz(0,0.1,0));
	else if (key == 123)
		op_addp(dir, op_mult_f(cross(g_rt.camera->dir, vector_xyz(0,1,0)), 0.1));
	else if (key == 124)
		op_addp(dir, op_mult_f(cross(vector_xyz(0,1,0), g_rt.camera->dir), 0.1));
	else
		op_addp(dir, vector_xyz(0,-0.1,0));
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
