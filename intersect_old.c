/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:49:03 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/09 19:49:01 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool pl_intersect(t_intersection *intersection, t_ray ray, void *shape)
{
	t_plane *p;
	float d;
	float t;
	(void)ray;

	p = (t_plane *)shape;
	d = dot(intersection->ray.direction, p->normal);
	if (d == 0)
		return (FALSE);
	t = dot(op_min(p->position, intersection->ray.origin), p->normal) / d;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > intersection->t)
		return (FALSE);
	intersection->t = t;
	intersection->shape = p;
	intersection->color = p->color;
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
	return (TRUE);
}

t_bool tr_intersect(t_intersection *intersection, t_ray r, void *shape)
{
	t_triangle *tr;
	t_vector q;
	double d;
	double u;
	double t;

	tr = (t_triangle *)shape;
	r.direction = cross(intersection->ray.direction, tr->e2);
	if ((d = dot(tr->e1, r.direction)) < EPSILON)
		return (FALSE);
	r.origin = op_min(intersection->ray.origin, tr->c1);
	u = dot(r.origin, r.direction);
	if (u < 0.0 || u > d)
		return (FALSE);
	q = cross(r.origin, tr->e1);
	if (dot(intersection->ray.direction, q) < 0.0 || u + v > d)
		return (FALSE);
	t = dot(tr->e2, q);
	(d != 0) ? t /= d : 0;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > intersection->t)
		return (FALSE);
	intersection->t = t;
	intersection->shape = tr;
	intersection->color = tr->color;
	return (TRUE);
}
//
// static	t_bool inside_tr(t_triangle *t, t_point p)
// {
// 	t_vector c0;
// 	t_vector c1;
// 	t_vector c2;
//
// 	c0 = op_min(p, t->c1);
// 	if (dot(t->n, cross(t->c1, c0)) < 0)
// 		return (FALSE);
// 	c1 = op_min(p, t->c2);
// 	if (dot(t->n, cross(t->c2, c1)) < 0)
// 		return (FALSE);
// 	c2 = op_min(p, t->c3);
// 	if (dot(t->n, cross(t->c3, c2)) < 0)
// 		return (FALSE);
// 	return (TRUE);
// }
//
// t_bool tr_intersect(t_intersection *intersection, t_ray ray, void *shape)
// {
// 	t_triangle *tr;
// 	t_vector inside;
// 	double t;
// 	double d;
//
// 	tr = (t_triangle *)shape;
// 	d = dot(intersection->ray.direction, tr->n);
// 	if (d == 0)
// 		return (FALSE);
// 	t = dot(op_min(tr->c1, intersection->ray.origin), tr->n) / d;
// 	if (t <= 0)
// 		return (FALSE);
// 	inside = op_add(ray.origin, op_mult_f(intersection->ray.direction, t));
// 	// printf("%f %f %f %f\n", t, inside.x, inside.y, inside.z);
// 	if (!(inside_tr(tr, inside)))
// 		return (FALSE);
// 	// printf("%f\n", t);
// 	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > intersection->t)
// 		return (FALSE);
// 	intersection->t = t;
// 	intersection->shape = tr;
// 	intersection->color = tr->color;
// 	return (TRUE);
// }

//
// t_bool tr_intersect(t_intersection *intersection, t_ray ray, void *shape)
// {
// 	t_triangle *tr;
// 	t_vector inside;
// 	double t;
// 	double div;
//
// 	tr = (t_triangle *)shape;
// 	div = dot(tr->n, ray.direction);
// 	if (div == 0.0)
// 		return (FALSE);
// 	// d = dot(tr->n, tr->c1); // nahh
// 	t = (dot(tr->n, ray.origin) + dot(tr->n, tr->c1)) / div;
// 	if (t <= 0)
// 		return (FALSE);
// 	inside = op_add(ray.origin, op_mult_f(ray.direction, t));
// 	// printf("%f %f %f %f\n", t, inside.x, inside.y, inside.z);
// 	if (!(inside_tr(tr, inside, inside)))
// 		return (FALSE);
// 	printf("%f\n", t);
// 	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > intersection->t)
// 		return (FALSE);
// 	intersection->t = t;
// 	intersection->shape = tr;
// 	intersection->color = tr->color;
// 	return (TRUE);
// }
//
// static	t_bool inside_tr(t_vector n, t_triangle *t, t_point p, t_vector e0)
// {
// 	t_vector e1;
// 	t_vector e2;
// 	t_vector c0;
// 	t_vector c1;
// 	t_vector c2;
//
// 	e0 = op_min(t->c2, t->c1);
// 	e1 = op_min(t->c3, t->c2);
// 	e2 = op_min(t->c1, t->c3);
// 	c0 = op_min(p, t->c1);
// 	c1 = op_min(p, t->c2);
// 	c2 = op_min(p, t->c3);
// 	if (dot(n, cross(e0, c0)) > 0 && dot(n, cross(e1, c1)) > 0 &&
// 	dot(n, cross(e2, c2)) > 0)
// 		return (TRUE);
// 	else
// 		return (FALSE);
// }
//
// t_bool tr_intersect(t_intersection *intersection, t_ray ray, void *shape)
// {
// 	t_triangle *tr;
// 	t_vector normal;
// 	t_vector inside;
// 	double t;
// 	double d;
// 	double div;
//
// 	tr = (t_triangle *)shape;
// 	normal = normalized(cross(op_min(tr->c2, tr->c1), op_min(tr->c3, tr->c1)));
// 	div = dot(normal, ray.direction);
// 	if (div == 0.0)
// 		return (FALSE);
// 	d = dot(normal, tr->c1); // nahh
// 	t = (dot(normal, ray.origin) + d) / div;
// 	if (t < 0)
// 		return (FALSE);
// 	inside = op_add(ray.origin, op_mult_f(ray.direction, t));
// 	if (inside_tr(normal, tr, inside, inside) == FALSE)
// 		return (FALSE);
// 	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > intersection->t)
// 		return (FALSE);
// 	intersection->t = t;
// 	intersection->shape = tr;
// 	intersection->color = tr->color;
// 	return (TRUE);
// }
