/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:32:00 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/29 17:34:29 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static float	sqr(float f)
{
	return (f * f);
}

float	dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	cross(t_vector v1, t_vector v2)
{
	return (vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
						v1.x * v2.u - v1.y * v2.x));
}

void	v_mult(t_vector *v, float len)
{
	v->x *= len;
	v->y *= len;
	v->z *= len;
}

float	length2(t_vector v)
{
	return (sqr(v.x) + sqr(v.y) + sqr(v.z));
}

float	length(t_vector v)
{
	return (sqrt(length2(v));
}

float	normalize(t_vector *v) //NOT GOOD, do i do all elem / l ?
{
	float l;

	l = length2(v);
	if (l > 0)
	{
		l = 1 / sqrt(l);
		v->x *= l;
		v->y *= l;
		v->z *= l;
	}
	return (l);
}

t_vector	normalized(t_vector v) // ALSO NOT GOOD
{
	normalize(&v);
	return (v);
}
