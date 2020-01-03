/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:49:03 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/03 17:46:17 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_bool	hit_pl(t_intersection *i, t_ray ray, void *shape)
{
	t_plane		*p;
	double		d;
	double		t;

	p = (t_plane *)shape;
	d = dot(ray.direction, p->normal);
	if (d == 0)
		return (FALSE);
	t = dot(op_min(p->position, ray.origin), p->normal) / d;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > i->t || t == 0.0)
		return (FALSE);
	i->t = t;
	i->shape = p;
	i->color = p->color;
	i->hit = op_add(ray.origin, op_mult_f(ray.direction, t));
	i->normal = normalized(p->normal);
	i->normal = (dot(p->normal, ray.direction) < 0) ? p->normal : op_mult_f(p->normal, -1.0);
	return (2);
}

static t_bool		hit_tr(t_intersection *i, t_ray ray, void *shape)
{
	t_triangle	*tr;
	t_vector	n;
	t_vector	p;
	double		t;
	double		d;

	tr = (t_triangle *)shape;
	n = normalized(cross(tr->e1, tr->e2));
	d = dot(ray.direction, n);
	if (d == 0)
		return (FALSE);
	t = dot(op_min(tr->c1, ray.origin), n) / d;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > i->t || t == 0.0)
		return (FALSE);
	p = op_add(i->ray.origin, op_mult_f(i->ray.direction, t));
	if (dot(tr->e3, op_min(p, tr->c1)) < 0 || dot(tr->e1, op_min(p, tr->c2)) < 0
		|| dot(tr->e2, op_min(p, tr->c3)) < 0)
		return (FALSE);
	i->t = t;
	i->shape = tr;
	i->color = tr->color;
	i->hit = p;
	i->normal = n;
	if (dot(i->normal, i->ray.direction) < 0)
		i->normal = op_mult_f(i->normal, -1.0);
	return (4);
}

static t_bool			hit_sq(t_intersection *i, t_ray ray, void *shape)
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
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > i->t || t == 0.0)
		return (FALSE);
	q = op_min(op_add(i->ray.origin, op_mult_f(i->ray.direction, t)), sq->center);
	side = normalized(cross(sq->normal, vector_xyz(1, 0, 0)));
	if (fabs(dot(q, side)) > sq->side || fabs(dot(cross(sq->normal, side), q)) > sq->side)
		return (FALSE);
	i->t = t;
	i->shape = sq;
	i->color = sq->color;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.direction, t));
	i->normal = (dot(sq->normal, i->ray.direction) < 0) ? sq->normal : op_mult_f(sq->normal, -1.0);
	return (5);
}

static t_bool			hit_sp(t_intersection *i, t_ray ray, void *shape)
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
	if (!(t > RAY_T_MIN && t < RAY_T_MAX) || t > i->t || t == 0.0)
		t = (-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a);
	if (t > RAY_T_MIN && t < RAY_T_MAX && t < i->t && t != 0.0)
		i->t = t;
	else
		return (FALSE);
	i->shape = (void *)sphere;
	i->t = t;
	i->color = sphere->color;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.direction, t));
	i->normal = normalized(op_min(i->hit, sphere->center));
	return (1);
}

static double		get_t(double a, double b, double d, t_cyl *cy, t_ray ray)
{
	double	t1;
	double	t2;
	double l1;
	double l2;

	t1 = (-b - sqrt(d)) / (2 * a);
	t2 = (-b + sqrt(d)) / (2 * a);
	l1 = dot(op_min(op_add(ray.origin, op_mult_f(ray.direction, t1)), cy->position), cy->direction);
	l2 = dot(op_min(op_add(ray.origin, op_mult_f(ray.direction, t2)), cy->position), cy->direction);
	if (t1 > 0.000001 && (t1 <= t2 || t2 < 0.000001) && fabs(l1) <= cy->h)
	{
		cy->first = 1;
		cy->d = l1;
		return (t1);
	}
	if (t2 > 0.0000001 && fabs(l2) <= cy->h)
	{
		cy->first = 0;
		cy->d = l2;
		return (t2);
	}
	return (-1);
}

static t_vector cyl_normal(t_cyl *c, t_point hit)
{
	t_vector n;
	t_vector to;

	to = op_add(c->position, op_mult_f(c->direction, c->d));

	if (c->first == 1)
		n = normalized(op_min(hit, to));
	else
		n = normalized(op_min(to, hit));
	return (n);
}

static t_bool			hit_cy(t_intersection *i, t_ray ray, void *shape)
{
	t_cyl	*cy;
	t_vector x;
	double	a;
	double	b;
	double	d;

	cy = (t_cyl *)shape;
	x = op_min(ray.origin, cy->position);
	a = dot(ray.direction, cy->direction);
	a = dot(ray.direction, ray.direction) - a * a;
	b = 2 * (dot(ray.direction, x) - dot(ray.direction, cy->direction) * dot(x, cy->direction));
	d = dot(x, cy->direction);
	d = dot(x, x) - d * d - cy->r * cy->r;
	d = b * b - 4 * a * d;
	d = (fabs(d) < 0.00001) ? 0 : get_t(a, b, d, cy, ray);
	if (d > 0 && d < i->t)
	{
		i->shape = (void *)cy;
		i->t = d;
		i->color = cy->color;
		i->hit = op_add(ray.origin, op_mult_f(ray.direction, d));
		i->normal = cyl_normal(cy, i->hit);
		return (3);
	}
	return (FALSE);
}

t_bool intersect(t_intersection *hit, t_ray ray, t_shapes *shape, int f)
{
	t_intersection fake;

	fake.t = hit->t;
	fake.ray = ray;
	if (shape->id == sp && f == 0)
		return(hit_sp(hit, ray, shape->shape));
	else if (shape->id == pl && f == 0)
		return(hit_pl(hit, ray, shape->shape));
	else if (shape->id == cy && f == 0)
		return(hit_cy(hit, ray, shape->shape));
	else if (shape->id == tr && f == 0)
		return(hit_tr(hit, ray, shape->shape));
	else if (shape->id == sq && f == 0)
		return(hit_sq(hit, ray, shape->shape));
	else if (shape->id == 0)
		return(hit_sp(&fake, ray, shape->shape));
	else if (shape->id == 1)
		return(hit_pl(&fake, ray, shape->shape));
	else if (shape->id == 2)
		return(hit_cy(&fake, ray, shape->shape));
	else if (shape->id == 3)
		return(hit_tr(&fake, ray, shape->shape));
	else if (shape->id == 4)
		return(hit_sq(&fake, ray, shape->shape));
	else
		return (FALSE);
}
