/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:58:45 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/02 16:00:13 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void op_min(t_vector *v, t_vector op)
{
	v->x -= op.x;
	v->y -= op.y;
	v->z -= op.z;
}

t_bool	sp_intersect(t_intersection *intersection, t_sphere sphere)
{
	t_ray ray;
	float a;
	float b;
	float c;
	float t;

	ray = vector_cpy(intersection->ray);
	op_min(&ray, sphere.centre); // might have to use math ft
	a = length2(ray.direction);
	b = 2 * dot(ray.direction, ray.origin);
	c = length2(ray.origin) - sqr(sphere.radius);
	if ((sqr(b) - 4 * a * c) < 0.0)
		return (false);
	t = (-b - sqrt(sqr(b) - 4 * a * c)) / (2 * a);
	if (!(t > RAY_T_MIN && t < RAY_T_MAX)) //add comparison to existing t && t < intersection.t
		t = (-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a));
	if (t > RAY_T_MIN && t < RAY_T_MAX)
		intersection->t = t;
	else
		return (false);
	intersection->shape = &sphere;
	return (true);
}
