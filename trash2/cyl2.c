/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 16:33:10 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/13 15:18:53 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
//
// static double	get_t(double t1, double t2, t_cyl *cy, t_ray r)
// {
// 	double		l1;
// 	double		l2;
//
// 	l1 = dot(op_min(op_add(r.origin, op_mult_f(r.dir, t1)), cy->pos), cy->dir);
// 	l2 = dot(op_min(op_add(r.origin, op_mult_f(r.dir, t2)), cy->pos), cy->dir);
// 	if (t1 > EPSILON && (t1 <= t2 || t2 < EPSILON) && fabs(l1) <= cy->h)
// 	{
// 		cy->first = 1;
// 		cy->d = l1;
// 		return (t1);
// 	}
// 	if (fabs(l1) > cy->h && fabs(l2) <= cy->h)
// 	{
// 		cy->first = -1;
// 		cy->d = l1;
// 		return (t2);
// 	}
// 	if (t2 > EPSILON && fabs(l2) <= cy->h)
// 	{
// 		cy->first = -1;
// 		cy->d = l2;
// 		return (t2);
// 	}
// 	return (-1);
// }

static double	get_t(double t1, double t2, t_cyl *cy, t_ray r)
{
	double		l1;
	double		l2;

	l1 = dot(op_min(op_add(r.origin, op_mult_f(r.dir, t1)), cy->pos), cy->dir);
	l2 = dot(op_min(op_add(r.origin, op_mult_f(r.dir, t2)), cy->pos), cy->dir);
	if (t1 > EPSILON && (t1 <= t2 || t2 < EPSILON) && fabs(l1) <= cy->h)
	{
		cy->first = 1;
		cy->d = l1;
		return (t1);
	}
	if (t2 > EPSILON && fabs(l2) <= cy->h)
	{
		cy->first = 0;
		cy->d = l2;
		return (t2);
	}
	return (-1);
}

// static int	hit_pl(t_intersection *i, t_ray ray, void *shape)
// {
// 	t_plane		*p;
// 	double		d;
// 	double		t;
//
// 	p = (t_plane *)shape;
// 	d = dot(ray.dir, p->normal);
// 	if (d == 0)
// 		return (0);
// 	t = dot(op_min(p->pos, ray.origin), p->normal) / d;
// 	i->t = t;
// 	i->hit = op_add(ray.origin, op_mult_f(ray.dir, t));
// 	return (2);
// }

static t_vector	cyl_normal(t_cyl *c, t_point hit)
{
	t_vector	to;
	// t_plane		p;

	// if (c->first == -1)
	// {
	// 	p.normal = (c->d < 0) ? op_mult_f(c->dir, -1) : c->dir;
	// 	p.pos = op_add(c->pos, op_mult_f(c->dir, c->d));
	// 	hit_pl(i, i->ray, (void *)&p);
	// 	return (p.normal);
	// }
	to = op_add(c->pos, op_mult_f(c->dir, c->d));
	if (c->first == 1)
		return (normalized(op_min(hit, to)));
	else
		return (normalized(op_min(to, hit)));
}

void copy_shape(t_cyl *s, t_cyl *c)
{
	c->pos = s->pos;
	c->color = s->color;
	c->check = s->check;
	c->dir = s->dir;
	c->r = s->r;
	c->h = s->h;
	c->first = 0;
	c->d = 0;
}

int				hit_cy(t_intersection *i, t_ray ray, void *shape)
{
	t_cyl		cy;
	t_vector	x;
	double		a;
	double		b;
	double		d;

	// copy_shape((t_cyl *)shape, &cy);
	cy = *((t_cyl *)shape);
	x = op_min(ray.origin, cy.pos);
	a = dot(ray.dir, cy.dir);
	a = dot(ray.dir, ray.dir) - a * a;
	b = 2 * (dot(ray.dir, x) - dot(ray.dir, cy.dir) * dot(x, cy.dir));
	d = dot(x, cy.dir);
	d = dot(x, x) - d * d - cy.r * cy.r;
	d = b * b - 4 * a * d;
	d = (fabs(d) < EPSILON) ? 0 :
	get_t((-b - sqrt(d)) / (2 * a), (-b + sqrt(d)) / (2 * a), &cy, ray);
	if (!(d > 0 && d < i->t))
		return (0);
	i->shape = shape;
	i->t = d;
	i->hit = op_add(ray.origin, op_mult_f(ray.dir, d));
	i->normal = cyl_normal(&cy, i->hit);
	i->color = cy.color;
	if (cy.check == 1)
	{
		t_vector temp = cross(cy.dir, vector_xyz(1, 0, 0));
		i->uv.x = 0.5 + (atan2(dot(i->normal, temp), dot(i->normal, cross(cy.dir, temp))) * 0.159159);
		i->uv.y = (cy.d < 0) ? cy.d - 1 : cy.d;
		i->color = (((int)(i->uv.x * cy.r * 6) % 2 == 0 && (int)(i->uv.y) % 2 != 0) || ((int)(i->uv.x * cy.r * 6) % 2 != 0 && (int)(i->uv.y) % 2 == 0)) ? new_color(255 - cy.color.r, 255 - cy.color.g, 255 - cy.color.b) : cy.color;
	}
	return (3);
}
