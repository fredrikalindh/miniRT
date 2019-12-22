/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:32:00 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/22 18:30:11 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	sqr(double f)
{
	return (f * f);
}

double	dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	cross(t_vector v1, t_vector v2) // cross product returns normal from v1 & v2
{
	return (vector_xyz(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
						v1.x * v2.y - v1.y * v2.x));
}

double	length2(t_vector v)
{
	return (sqr(v.x) + sqr(v.y) + sqr(v.z));
}

double	length(t_vector v)
{
	return (sqrt(length2(v)));
}

double	normalize(t_vector *v)
{
	double l;
	double l2;

	l2 = length(*v);
	if (l2 > 0)
	{
		l = 1 / l2;
		v->x *= l;
		v->y *= l;
		v->z *= l;
	}
	return (l2);
}

t_vector	normalized(t_vector v)
{
	normalize(&v);
	return (v);
}
