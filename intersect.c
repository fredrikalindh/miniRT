/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:49:03 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/10 16:43:06 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool			pl_intersect(t_intersection *i, t_ray ray, void *shape)
{
	t_plane		*p;
	double		d;
	double		t;

	(void)ray;
	p = (t_plane *)shape;
	d = dot(i->ray.direction, p->normal);
	if (d == 0)
		return (FALSE);
	t = dot(op_min(p->position, i->ray.origin), p->normal) / d;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > i->t)
		return (FALSE);
	i->t = t;
	i->shape = p;
	i->color = p->color;
	return (TRUE);
}

t_bool			tr_intersect(t_intersection *i, t_ray r, void *shape)
{
	t_triangle	*tr;
	t_vector	q;
	t_vector	s;
	double		t;

	tr = (t_triangle *)shape;
	r.direction = cross(i->ray.direction, tr->e2);
	if ((s.x = dot(tr->e1, r.direction)) < EPSILON)
		return (FALSE);
	r.origin = op_min(i->ray.origin, tr->c1);
	s.y = dot(r.origin, r.direction);
	if (s.y < 0.0 || s.y > s.x)
		return (FALSE);
	q = cross(r.origin, tr->e1);
	s.z = dot(i->ray.direction, q);
	if (s.z < 0.0 || s.y + s.z > s.x)
		return (FALSE);
	t = dot(tr->e2, q);
	(s.x != 0) ? t /= s.x : 0;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > i->t)
		return (FALSE);
	i->t = t;
	i->shape = tr;
	i->color = tr->color;
	return (TRUE);
}

// t_bool			sq_intersect(t_intersection *i, t_ray r, void *shape)
// {
// 	t_square	*sq;
// 	t_vector	q;
// 	t_vector	d;
// 	double		t;
//
// 	sq = (t_square *)shape;
// 	d = dot(i->ray.direction, sq->normal);
// 	if (d == 0)
// 		return (FALSE);
// 	t = dot(op_min(sq->center, i->ray.origin), sq->normal) / d;
// 	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > i->t)
// 		return (FALSE);
//
// 	i->t = t;
// 	i->shape = sq;
// 	i->color = sq->color;
// 	return (TRUE);
// }

t_bool			sp_intersect(t_intersection *i, t_ray ray, void *shape)
{
	t_sphere	*sphere;
	double		a;
	double		b;
	double		c;
	double		t;

	sphere = (t_sphere *)shape;
	op_minv(&ray.origin, sphere->center);
	a = length2(ray.direction);
	b = 2 * dot(ray.direction, ray.origin);
	c = length2(ray.origin) - sqr(sphere->radius);
	if ((sqr(b) - 4 * a * c) < 0.0)
		return (FALSE);
	t = (-b - sqrt(sqr(b) - 4 * a * c)) / (2 * a);
	if (!(t > RAY_T_MIN && t < RAY_T_MAX) || t > i->t)
		t = (-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a);
	if (t > RAY_T_MIN && t < RAY_T_MAX && t < i->t)
		i->t = t;
	else
		return (FALSE);
	i->shape = (void *)sphere;
	i->t = t;
	i->color = sphere->color;
	return (TRUE);
}
//
// t_bool			cy_intersect(t_intersection *i, t_ray r, void *shape)
// {
// 	t_cyl		*cy;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		d;
// 	double		t;
//
// 	cy = (t_cyl *)shape;
// 	op_minv(&ray.origin, cy->direction);
// 	a = length2(ray.direction);
// 	b = 2 * dot(ray.direction, ray.origin);
// 	c = length2(ray.origin) - sqr(sphere->radius);
// }
