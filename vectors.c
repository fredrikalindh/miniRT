/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:32:00 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/19 13:33:00 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		normalize(t_vector *v)
{
	double		l;
	double		l2;

	l2 = length(*v);
	if (l2 > 0)
	{
		l = 1 / l2;
		v->x *= l;
		v->y *= l;
		v->z *= l;
	}
	if (v->x == 0 && v->y == 0 && v->z == 0)
		v->z = -1;
	return (l2);
}

t_vector	normalized(t_vector v)
{
	normalize(&v);
	return (v);
}

t_vector	vector_xyz(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
