/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:49:03 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/10 13:09:23 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	hit_pl(t_intersection *i, t_ray ray, void *shape)
{
	t_plane		*p;
	double		d;
	double		t;

	p = (t_plane *)shape;
	d = dot(ray.dir, p->normal);
	if (d == 0)
		return (0);
	t = dot(op_min(p->pos, ray.origin), p->normal) / d;
	if (t <= T_MIN || t >= T_MAX || t > i->t || t == 0.0)
		return (0);
	i->t = t;
	i->shape = p;
	i->color = p->color;
	i->hit = op_add(ray.origin, op_mult_f(ray.dir, t));
	i->normal = normalized(p->normal);
	if (dot(p->normal, ray.dir) > 0)
		i->normal = op_mult_f(i->normal, -1.0);
	return (2);
}

static int	hit_tr(t_intersection *i, t_ray r, void *shape)
{
	t_triangle	*tr;
	t_vector	p;
	double		t;

	tr = (t_triangle *)shape;
	p = cross(i->ray.dir, tr->e2);
	if (fabs(r.dir.x = dot(tr->e1, p)) < EPSILON)
		return (0);
	r.dir.x = 1 / r.dir.x;
	r.origin = op_min(i->ray.origin, tr->c1);
	if ((r.dir.y = dot(r.origin, p) * r.dir.x) < 0 || r.dir.y > 1)
		return (0);
	p = cross(r.origin, tr->e1);
	if ((r.dir.z = dot(i->ray.dir, p) * r.dir.x) < 0 || r.dir.z + r.dir.y > 1)
		return (0);
	if ((t = dot(tr->e2, p) * r.dir.x) >= T_MAX || t > i->t || fabs(t) < 0.0001)
		return (0);
	i->t = t;
	i->shape = tr;
	i->color = tr->color;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.dir, t));
	i->normal = normalized(cross(tr->e1, tr->e2));
	if (dot(i->normal, i->ray.dir) > 0)
		i->normal = op_mult_f(i->normal, -1.0);
	return (4);
}

static int	hit_sq(t_intersection *i, t_ray r, void *shape)
{
	t_square	*sq;
	t_vector	side;
	double		d;
	double		t;

	sq = (t_square *)shape;
	d = dot(i->ray.dir, sq->normal);
	if (d == 0)
		return (0);
	t = dot(op_min(sq->center, i->ray.origin), sq->normal) / d;
	if (t <= T_MIN || t >= T_MAX || t > i->t || t == 0.0)
		return (0);
	r.dir = op_min(op_add(i->ray.origin, op_mult_f(i->ray.dir, t)), sq->center);
	side = normalized(cross(sq->normal, vector_xyz(1, 0, 0)));
	if (fabs(dot(r.dir, side)) > sq->side ||
		fabs(dot(cross(sq->normal, side), r.dir)) > sq->side)
		return (0);
	i->t = t;
	i->shape = sq;
	i->color = sq->color;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.dir, t));
	i->normal = (dot(sq->normal, i->ray.dir) < 0) ? sq->normal :
	op_mult_f(sq->normal, -1.0);
	return (5);
}

static int	hit_sp(t_intersection *i, t_ray ray, void *shape)
{
	t_sphere	*sphere;
	double		a;
	double		b;
	double		c;
	double		t;

	sphere = (t_sphere *)shape;
	op_minv(&ray.origin, sphere->center);
	a = length2(ray.dir);
	b = 2 * dot(ray.dir, ray.origin);
	c = length2(ray.origin) - sqr(sphere->radius);
	if ((sqr(b) - 4 * a * c) < 0.0)
		return (0);
	t = (-b - sqrt(sqr(b) - 4 * a * c)) / (2 * a);
	if (!(t > T_MIN && t < T_MAX) || t > i->t || t == 0.0)
	{
		t = (-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a);
		a = -1;
	}
	if (!(t > T_MIN && t < T_MAX && t < i->t && t != 0.0))
		return (0);
	i->shape = (void *)sphere;
	i->t = t;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.dir, t));
	i->normal = a != -1 ? normalized(op_min(i->hit, sphere->center)) :
	normalized(op_min(sphere->center, i->hit));
	i->color = sphere->color;
	// i->tex.x = (1 + atan2(i->hit.z, i->hit.x) / 3.1415) * 10;
	// i->tex.y = cos(i->hit.y) / 3.1415 * 5;
	// printf("%f %f\n", i->tex.x, i->tex.y);
	// i->color = ((((int)i->tex.x) % 2 == 0 && ((int)i->tex.y) % 2 != 0) || (((int)i->tex.x) % 2 != 0 && ((int)i->tex.y) % 2 == 0)) ? same_color(255) : sphere->color;
	// i->color = ((i->tex.x >= 0.5 && i->tex.x <= 0.7) || (i->tex.x >= 0.0 && i->tex.x <= 0.2)) ? same_color(255) : sphere->color;
	// i->color = ((i->tex.x * 20 > 0.5 && i->tex.y * 20 < 0.5) ||
	// 			(i->tex.x * 10 > 0) ||
	// 			(i->tex.x * 20 == 0.8 && i->tex.y * 20 == 0.8)) ? same_color(255) : sphere->color;
	return (1);
}

int			intersect(t_intersection *hit, t_ray ray, t_shapes *shape, int f)
{
	t_intersection fake;

	fake.ray = ray;
	if ((fake.t = hit->t) != 0 && shape->id == sp && f == 0)
		return (hit_sp(hit, ray, shape->shape));
	else if (shape->id == pl && f == 0)
		return (hit_pl(hit, ray, shape->shape));
	else if (shape->id == cy && f == 0)
		return (hit_cy(hit, ray, shape->shape));
	else if (shape->id == tr && f == 0)
		return (hit_tr(hit, ray, shape->shape));
	else if (shape->id == sq && f == 0)
		return (hit_sq(hit, ray, shape->shape));
	else if (shape->id == 0)
		return (hit_sp(&fake, ray, shape->shape));
	else if (shape->id == 1)
		return (hit_pl(&fake, ray, shape->shape));
	else if (shape->id == 2)
		return (hit_cy(&fake, ray, shape->shape));
	else if (shape->id == 3)
		return (hit_tr(&fake, ray, shape->shape));
	else if (shape->id == 4)
		return (hit_sq(&fake, ray, shape->shape));
	else
		return (0);
}
