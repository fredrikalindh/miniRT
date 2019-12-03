/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:49:03 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/03 16:00:37 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// t_bool p_intersect(t_ray ray, t_intersection *intersection)
// {
// 	float dDotN;
// 	float t;
//
// 	dDotN = dot(intersection->ray.direction, plane.normal);
// 	if (dDotN == 0)
// 		return (false);
// 	t = dot(plane.position - intersection, ray.origin.normal) / dDotN; // nahh
// 	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > intersection.t)
// 		return (false);
// 	intersection->t = t;
// 	intersection->shape = &plane;
// 	return (true);
// }

t_bool	sp_intersect(t_ray ray, t_intersection *intersection)
{
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
	if (!(t > RAY_T_MIN && t < RAY_T_MAX) || t > intersection.t) //add comparison to existing t && t < intersection.t
		t = (-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a));
	if ((t > RAY_T_MIN && t < RAY_T_MAX) || t > intersection.t)
		intersection->t = t;
	else
		return (false);
	intersection->shape = &sphere;
	return (true);
}
