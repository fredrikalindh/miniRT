/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:49:03 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/04 19:23:14 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool pl_intersect(t_intersection *intersection, t_ray ray, void *shape)
{
	t_plane *plane;
	float normal;
	float t;
	(void)ray;

	plane = (t_plane *)shape;
	normal = dot(intersection->ray.direction, plane->normal);
	if (normal == 0)
		return (FALSE);
	t = dot(op_min(plane->position, intersection->ray.origin), plane->normal) / normal; // nahh
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > intersection->t)
		return (FALSE);
	intersection->t = t;
	intersection->shape = plane;
	intersection->color = plane->color;
	return (TRUE);
}


t_bool	sp_intersect(t_intersection *intersection, t_ray ray, void *shape)
{
	t_sphere *sphere;
	float a;
	float b;
	float c;
	float t;

	sphere = (t_sphere *)shape;
	op_minv(&ray.origin, sphere->center);
	a = length2(ray.direction);
	b = 2 * dot(ray.direction, ray.origin);
	c = length2(ray.origin) - sqr(sphere->radius);
	if ((sqr(b) - 4 * a * c) < 0.0)
		return (FALSE);
	t = (-b - sqrt(sqr(b) - 4 * a * c)) / (2 * a);
	if (!(t > RAY_T_MIN && t < RAY_T_MAX) || t > intersection->t)
		t = (-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a);
	if (t > RAY_T_MIN && t < RAY_T_MAX && t < intersection->t)
		intersection->t = t;
	else
		return (FALSE);
	intersection->shape = (void *)sphere;
	intersection->t = t;
	intersection->color = sphere->color;
	// printf("%d %d %d\n", sphere->color.r, sphere->color.g,  sphere->color.b);
	return (TRUE);
}

static	t_bool inside_tr(t_vector n, t_triangle *t, t_point p, t_vector e0)
{
	t_vector e1;
	t_vector e2;
	t_vector c0;
	t_vector c1;
	t_vector c2;

	e0 = op_min(t->c2, t->c1);
	e1 = op_min(t->c3, t->c2);
	e2 = op_min(t->c1, t->c3);
	c0 = op_min(p, t->c1);
	c1 = op_min(p, t->c2);
	c2 = op_min(p, t->c3);
	if (dot(n, cross(e0, c0)) > 0 && dot(n, cross(e1, c1)) > 0 &&
	dot(n, cross(e2, c2)) > 0)
		return (TRUE);
	else
		return (FALSE);
}

t_bool tr_intersect(t_intersection *intersection, t_ray ray, void *shape)
{
	t_triangle *triangle;
	t_vector normal;
	t_vector inside;
	float t;
	float d;
	float dDot;

	triangle = (t_triangle *)shape;
	normal = normalized(cross(op_min(triangle->c2, triangle->c1), op_min(triangle->c3, triangle->c1)));
	dDot = dot(normal, ray.direction);
	if (dDot == 0)
		return (FALSE);
	d = dot(normal, triangle->c1); // nahh
	t = -(dot(normal, ray.origin) + d) / dDot;
	inside = op_add(ray.origin, op_mult_f(ray.direction, t));
	if (inside_tr(normal, triangle, inside, inside) == FALSE)
		return (FALSE);
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > intersection->t)
		return (FALSE);
	intersection->t = t;
	intersection->shape = triangle;
	intersection->color = triangle->color;
	return (TRUE);
}
