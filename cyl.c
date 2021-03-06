/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 16:33:10 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/19 13:32:02 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static t_vector	cyl_normal(t_cyl *c, t_point hit)
{
	t_vector	to;

	to = op_add(c->pos, op_mult_f(c->dir, c->d));
	if (c->first == 1)
		return (normalized(op_min(hit, to)));
	else
		return (normalized(op_min(to, hit)));
}

int				hit_cy(t_intersection *i, t_ray ray, void *shape)
{
	t_cyl		cy;
	t_vector	x;
	double		a;
	double		b;
	double		d;

	cy = *((t_cyl *)shape);
	x = op_min(ray.origin, cy.pos);
	a = dot(ray.dir, ray.dir) - sqr(dot(ray.dir, cy.dir));
	b = 2 * (dot(ray.dir, x) - dot(ray.dir, cy.dir) * dot(x, cy.dir));
	d = dot(x, x) - sqr(dot(x, cy.dir)) - cy.r * cy.r;
	d = b * b - 4 * a * d;
	d = (fabs(d) < EPSILON) ? 0 :
	get_t((-b - sqrt(d)) / (2 * a), (-b + sqrt(d)) / (2 * a), &cy, ray);
	if (!(d > 0 && d < i->t))
		return (0);
	i->shape = shape;
	i->t = d;
	i->hit = op_add(ray.origin, op_mult_f(ray.dir, d));
	i->normal = cyl_normal(&cy, i->hit);
	x = cross(cy.dir, vector_xyz(1, 0, 0));
	i->color = (cy.check == 1) ? checked((0.5 + (atan2(dot(i->normal, x),
	dot(i->normal, cross(cy.dir, x))) * 0.159159)) * cy.r * 6, cy.d, cy.color) :
	cy.color;
	return (3);
}
