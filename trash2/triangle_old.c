/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle_old.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 15:19:52 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/04 15:23:08 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


static t_bool		hit_tr(t_intersection *i, t_ray r, void *shape)
{
	t_triangle	*tr;
	t_vector	q;
	t_vector	s;
	double		d;
	double		t;

	tr = (t_triangle *)shape;
	r.direction = cross(tr->e1, tr->e2);
	if ((d = dot(i->ray.direction, r.direction)) == 0)
		return (FALSE)
	t = dot(op_min(p->position, ray.origin), p->normal) / d;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > i->t || t == 0.0)
		return (FALSE);
	r.origin = op_add(i->ray.origin, op_mult_f(i->ray.direction, t);
	if ()
	i->t = t;
	i->shape = tr;
	i->color = tr->color;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.direction, t));
	i->normal = normalized(cross(tr->e1, tr->e2));
	if (dot(i->normal, i->ray.direction) > 0)
		i->normal = op_mult_f(i->normal, -1.0);
	return (4);
}

static t_bool		hit_tr(t_intersection *i, t_ray r, void *shape)
{
	t_triangle	*tr;
	t_vector	q;
	t_vector	s;
	double		t;
	int			flag;

	tr = (t_triangle *)shape;
	r.direction = cross(i->ray.direction, tr->e2);
	flag = (s.x = dot(tr->e1, r.direction)) < 0.00001) ? -1 : 1;
	r.origin = op_min(i->ray.origin, tr->c1);
	s.y = dot(r.origin, r.direction);
	if ((s.y < 0.000001 && flag != -1) || s.y > s.x)
		return (FALSE);
	q = cross(r.origin, tr->e1);
	s.z = dot(i->ray.direction, q);
	if ((s.z < 0.000001 && flag != -1) || s.y + s.z > s.x)
		return (FALSE);
	t = dot(tr->e2, q);
	(s.x != 0) ? t /= s.x : 0;
	if (t <= RAY_T_MIN || t >= RAY_T_MAX || t > i->t || t == 0.0)
		return (FALSE);
	i->t = t;
	i->shape = tr;
	i->color = tr->color;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.direction, t));
	i->normal = normalized(cross(tr->e1, tr->e2));
	if (dot(i->normal, i->ray.direction) > 0)
		i->normal = op_mult_f(i->normal, -1.0);
	return (4);
}
