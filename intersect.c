/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:49:03 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/21 17:28:30 by frlindh          ###   ########.fr       */
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
	i->normal = p->normal;
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
	i->normal = cross(tr->e1, tr->e2);
	return (TRUE);
}

t_bool			sq_intersect(t_intersection *i, t_ray ray, void *shape)
{
	t_square	*sq;
	t_vector	q;
	t_vector	side;
	double		d;
	double		t;
	(void)ray;

	sq = (t_square *)shape;
	d = dot(i->ray.direction, sq->normal);
	if (d == 0)
		return (FALSE);
	t = dot(op_min(sq->center, i->ray.origin), sq->normal) / d;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > i->t)
		return (FALSE);
	q = op_min(op_add(i->ray.origin, op_mult_f(i->ray.direction, t)), sq->center);
	side = cross(sq->normal, vector_xyz(0, 1, 0));
	if (dot(q, side) > sq->side || dot(q, side) < -sq->side ||
		fabs(dot(cross(sq->normal, side), q)) > sq->side)
		return (FALSE);
	i->t = t;
	i->shape = sq;
	i->color = sq->color;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.direction, t));
	i->normal = sq->normal;
	return (TRUE);
}

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
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.direction, t));
	i->normal = normalized(op_min(i->hit, sphere->center));
	return (TRUE);
}

double		get_t(double a, double b, double d, t_cyl *cy, t_ray ray)
{
	double	t1;
	double	t2;
	double l1;
	double l2;

	t1 = (-b - sqrt(d)) / (2 * a);
	t2 = (-b + sqrt(d)) / (2 * a);
	l1 = dot(op_min(op_add(ray.origin, op_mult_f(ray.direction, t1)), cy->position), cy->direction);
	l2 = dot(op_min(op_add(ray.origin, op_mult_f(ray.direction, t2)), cy->position), cy->direction);
	if ((t2 < 0 || t2 >= t1) && t1 > 0 && fabs(l1) < cy->h)
		return (t1);
	if (t2 > 0 && fabs(l2) < cy->h)
		return (t2);
	return (-1);
}

t_bool			cy_intersect(t_intersection *i, t_ray ray, void *shape)
{
	t_cyl	*cy;
	t_vector x;
	double	a;
	double	b;
	double	c;
	double	d;

	cy = (t_cyl *)shape;
	x = op_min(ray.origin, cy->position);
	a = dot(ray.direction, cy->direction);
	a = dot(ray.direction, ray.direction) - a * a;
	b = 2 * (dot(ray.direction, x) - dot(ray.direction, cy->direction) * dot(x, cy->direction));
	c = dot(x, cy->direction);
	c = dot(x, x) - c * c - cy->r * cy->r;
	d = b * b - 4 * a * c;
	d = (fabs(d) < 0.00001) ? 0 : get_t(a, b, d, cy, ray);
	if (d > 0 && d < i->t)
	{
		i->shape = (void *)cy;
		i->t = d;
		i->color = cy->color;
		i->hit = op_add(ray.origin, op_mult_f(ray.direction, d));
		i->normal = op_min(i->hit, cy->position);
		return (TRUE);
	}
	return (FALSE);
}
