/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:49:03 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/13 15:16:20 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	hit_pl(t_intersection *i, t_ray r, void *shape)
{
	t_plane		*p;
	double		d;
	double		t;

	p = (t_plane *)shape;
	d = dot(r.dir, p->normal);
	if (d == 0)
		return (0);
	t = dot(op_min(p->pos, r.origin), p->normal) / d;
	if (t <= T_MIN || t >= T_MAX || t > i->t || t == 0.0)
		return (0);
	i->t = t;
	i->shape = p;
	i->color = p->color;
	i->hit = op_add(r.origin, op_mult_f(r.dir, t));
	i->normal = normalized(p->normal);
	if (dot(p->normal, r.dir) > 0)
		i->normal = op_mult_f(i->normal, -1.0);
	r.dir =
	normalized(cross(i->normal, op_min(vector_xyz(1, 1, 0), i->normal)));
	i->color = (p->check == 1) ? checked(dot(op_min(p->pos, i->hit), r.dir) / 6,
		dot(op_min(p->pos, i->hit), cross(i->normal, r.dir)) / 6, p->color)
		: p->color;
	return (2);
}

static int	hit_tr(t_intersection *i, t_ray r, void *shape)
{
	t_triangle	*tr;
	t_vector	p;
	double		t;

	tr = (t_triangle *)shape;
	p = cross(i->ray.dir, tr->e2);
	if (fabs(r.dir.x = dot(tr->e1, p)) > EPSILON)
		r.dir.x = 1 / r.dir.x;
	r.origin = op_min(r.origin, tr->c1);
	if ((r.dir.y = dot(r.origin, p) * r.dir.x) < 0 || r.dir.y > 1)
		return (0);
	p = cross(r.origin, tr->e1);
	if ((r.dir.z = dot(i->ray.dir, p) * r.dir.x) < 0 || r.dir.z + r.dir.y > 1)
		return (0);
	if ((t = dot(tr->e2, p) * r.dir.x) >= T_MAX || t > i->t || t < 0.0001)
		return (0);
	i->t = t;
	i->shape = tr;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.dir, t));
	i->normal = (dot(normalized(cross(tr->e1, tr->e2)), i->ray.dir) > 0) ?
	normalized(cross(tr->e2, tr->e1)) : normalized(cross(tr->e1, tr->e2));
	p = normalized(cross(i->normal, op_min(vector_xyz(1, 1, 0), i->normal)));
	i->color = (tr->check == 1) ? checked(dot(op_min(tr->c1, i->hit), p),
	dot(op_min(tr->c1, i->hit), cross(i->normal, p)), tr->color) : tr->color;
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
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.dir, t));
	i->normal = (dot(sq->normal, i->ray.dir) < 0) ? sq->normal :
	op_mult_f(sq->normal, -1.0);
	i->color = (sq->check == 1) ? checked(dot(op_min(sq->center, i->hit), side),
dot(op_min(sq->center, i->hit), cross(i->normal, side)), sq->color) : sq->color;
	return (5);
}

static int	hit_sp(t_intersection *i, t_ray r, void *shape)
{
	t_sphere	*sp;
	double		d;
	double		t;

	sp = (t_sphere *)shape;
	op_minv(&r.origin, sp->center);
	r.dir = vector_xyz(length2(i->ray.dir), 2 * dot(i->ray.dir, r.origin),
	length2(r.origin) - sqr(sp->radius));
	if ((d = (sqr(r.dir.y) - 4 * r.dir.x * r.dir.z)) < 0.0)
		return (0);
	t = (-r.dir.y - sqrt(d)) / (2 * r.dir.x);
	if ((!(t > T_MIN && t < T_MAX) || t > i->t || t == 0.0) &&
	(t = (-r.dir.y + sqrt(d)) / (2 * r.dir.x)) != 0)
		r.dir.x = -1;
	if (!(t > T_MIN && t < T_MAX && t < i->t && t != 0.0))
		return (0);
	i->shape = (void *)sp;
	i->t = t;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.dir, t));
	i->normal = r.dir.x != -1 ? normalized(op_min(i->hit, sp->center)) :
	normalized(op_min(sp->center, i->hit));
	i->color = (sp->check == 1) ? checked((0.5 + (atan2(i->normal.z,
		i->normal.x) * 0.159159)) * sp->radius * 4, (1 - (acos(i->normal.y) *
		0.31832)) * sp->radius * 2, sp->color) : sp->color;
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
