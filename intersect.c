/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:49:03 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/04 16:48:31 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// t_bool p_intersect(t_intersection *intersection)
// {
	// t_ray ray;
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

// t_bool	sp_intersect(t_intersection *intersection, t_ray ray, void *shape)
// {
// 	t_sphere *sphere;
// 	float a;
// 	float b;
// 	float c;
// 	float t;
//
// 	sphere = (t_sphere *)shape;
// 	op_minv(&ray.origin, sphere->center);
// 	a = length2(ray.direction);
// 	b = 2 * dot(ray.direction, ray.origin);
// 	c = length2(ray.origin) - sqr(sphere->radius);
// 	if ((sqr(b) - 4 * a * c) < 0.0)
// 		return (FALSE);
// 	t = (-b - sqrt(sqr(b) - 4 * a * c)) / (2 * a);
// 	if (!(t > RAY_T_MIN && t < RAY_T_MAX) || t > intersection->t)
// 		t = (-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a);
// 	if ((t > RAY_T_MIN && t < RAY_T_MAX) || t > intersection->t)
// 		intersection->t = t;
// 	else
// 		return (FALSE);
// 	// printf("%d\n", sphere->color.r);
// 	intersection->shape = (void *)sphere;
// 	// printf("%d %d %d\n", sphere->color.r, sphere->color.g,  sphere->color.b);
// 	intersection->color = sphere->color; // remo
// 	return (TRUE);
// }

t_bool	sp_intersect(t_intersection *intersection, t_ray ray, void *shape)
{
	t_sphere *sphere;
	float a;
	float b;
	float c;
	float d;
	float t;

	sphere = (t_sphere *)shape;
	op_minv(&ray.origin, sphere->center);
	a = length2(ray.direction);
	b = 2 * dot(ray.direction, ray.origin);
	c = length2(ray.origin) - sqr(sphere->radius);
	d = sqr(b) - 4 * a * c;
	if (d < 0.0)
		return (FALSE);
	t = (-b - sqrt(d)) / (2 * a);
	if (!(t > RAY_T_MIN && t < RAY_T_MAX) || t > intersection->t)
		t = (-b + sqrt(d)) / (2 * a);
	if ((t > RAY_T_MIN && t < RAY_T_MAX) || t > intersection->t)
		intersection->t = t;
	else
		return (FALSE);
	intersection->shape = (void *)sphere;
	printf("%d %d %d\n", sphere->color.r, sphere->color.g,  sphere->color.b);
	intersection->color = sphere->color; // remo
	return (TRUE);
}
