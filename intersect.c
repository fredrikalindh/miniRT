/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:49:03 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/11 21:13:25 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	hit_pl(t_intersection *i, t_ray ray, void *shape)
{
	t_plane		*p;
	double		d;
	double		t;
	t_vector	temp;

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
	temp = normalized(cross(i->normal, op_min(vector_xyz(1, 1, 0), i->normal)));
	i->uv.x = dot(op_min(p->pos, i->hit), temp);
	i->uv.y = dot(op_min(p->pos, i->hit), cross(i->normal, temp));
	i->uv.x = (i->uv.x < 0) ? (int)(i->uv.x - 1) % 2 : (int)(i->uv.x) % 2;
	i->uv.y = (i->uv.y < 0) ? (int)(i->uv.y - 1) % 2 : (int)(i->uv.y) % 2;
	// printf("%f %f\n", i->uv.x, i->uv.y);
	i->color = ((i->uv.x == 0 && i->uv.y != 0) || (i->uv.x != 0 && i->uv.y == 0)) ? new_color(255 - p->color.r, 255 - p->color.g, 255 - p->color.b) : p->color;
	// i->uv.x = cross(i->normal, op_min(p->pos, ray.origin));
	// i->uv.y = 1 - (acos(i->normal.y) * 0.31832);
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
	if ((t = dot(tr->e2, p) * r.dir.x) >= T_MAX || t > i->t || t < 0.0001)
		return (0);
	i->t = t;
	i->shape = tr;
	i->color = tr->color;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.dir, t));
	i->normal = normalized(cross(tr->e1, tr->e2));
	if (dot(i->normal, i->ray.dir) > 0)
		i->normal = op_mult_f(i->normal, -1.0);
	t_vector temp = normalized(cross(i->normal, op_min(vector_xyz(1, 1, 0), i->normal)));
	i->uv.x = dot(op_min(tr->c1, i->hit), temp);
	i->uv.y = dot(op_min(tr->c1, i->hit), cross(i->normal, temp));
	i->uv.x = (i->uv.x < 0) ? (int)(i->uv.x - 1) % 2 : (int)(i->uv.x) % 2;
	i->uv.y = (i->uv.y < 0) ? (int)(i->uv.y - 1) % 2 : (int)(i->uv.y) % 2;
	// printf("%f %f\n", i->uv.x, i->uv.y);
	i->color = ((i->uv.x == 0 && i->uv.y != 0) || (i->uv.x != 0 && i->uv.y == 0)) ? new_color(255 - tr->color.r, 255 - tr->color.g, 255 - tr->color.b) : tr->color;
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
	i->uv.x = dot(op_min(sq->center, i->hit), side);
	i->uv.y = dot(op_min(sq->center, i->hit), cross(i->normal, side));
	i->uv.x = (i->uv.x < 0) ? (int)(i->uv.x - 1) % 2 : (int)(i->uv.x) % 2;
	i->uv.y = (i->uv.y < 0) ? (int)(i->uv.y - 1) % 2 : (int)(i->uv.y) % 2;
	// printf("%f %f\n", i->uv.x, i->uv.y);
	i->color = ((i->uv.x == 0 && i->uv.y != 0) || (i->uv.x != 0 && i->uv.y == 0)) ? new_color(255 - sq->color.r, 255 - sq->color.g, 255 - sq->color.b) : sq->color;
	return (5);
}

// t_image	open_bmp(char *name)
// {
// 	t_image	g;
// 	int		fd;
// 	// unsigned int	start;
// 	unsigned char	f[54];
//
// 	if (!(fd = open(name, O_RDONLY)))
// 		ft_puterr("failed to open texture file");
// 	// read(fd, f, 14);
// 	// start = 54;
// 	// read(fd, f, 54);
// 	g.w = (f[4]<<0) | (f[5]<<8) | (f[6]<<16) | (f[7]<<24);
// 	g.h = (f[8]<<0) | (f[9]<<8) | (f[10]<<16) | (f[11]<<24);
// 	g.w = 500;
// 	g.h = 500;
// 	g.data = (char *)malloc(g.w * g.h * 3 + 54);
// 	read(fd, g.data, g.w * g.h * 3);
// 	// printf("[%c %c %c]\n", g.data[0], g.data[1], g.data[2]);
// 	close(fd);
// 	return (g);
// }
//
// t_color		set_color(t_image g, double x, double y)
// {
// 	int i;
// 	t_color c;
//
// 	i = x * g.w * 3 + y * g.h * 3 + 54;
// 	// printf("%d\n", g.data[i] + 100);
// 	c.b = g.data[i++] + 100;
// 	c.g = g.data[i++] + 100;
// 	c.r = g.data[i++] + 100;
// 	return (c);
// }

static int	hit_sp(t_intersection *i, t_ray r, void *shape)
{
	t_sphere	*sphere;
	double		d;
	double		t;

	sphere = (t_sphere *)shape;
	op_minv(&r.origin, sphere->center);
	r.dir.x = length2(i->ray.dir);
	r.dir.y = 2 * dot(i->ray.dir, r.origin);
	r.dir.z = length2(r.origin) - sqr(sphere->radius);
	if ((d = (sqr(r.dir.y) - 4 * r.dir.x * r.dir.z)) < 0.0)
		return (0);
	t = (-r.dir.y - sqrt(d)) / (2 * r.dir.x);
	if (!(t > T_MIN && t < T_MAX) || t > i->t || t == 0.0)
	{
		t = (-r.dir.y + sqrt(d)) / (2 * r.dir.x);
		r.dir.x = -1;
	}
	if (!(t > T_MIN && t < T_MAX && t < i->t && t != 0.0))
		return (0);
	i->shape = (void *)sphere;
	i->t = t;
	i->hit = op_add(i->ray.origin, op_mult_f(i->ray.dir, t));
	i->normal = r.dir.x != -1 ? normalized(op_min(i->hit, sphere->center)) :
	normalized(op_min(sphere->center, i->hit));
	// i->color = sphere->color;
	i->uv.x = 0.5 + (atan2(i->normal.z, i->normal.x) * 0.159159);
	i->uv.y = 1 - (acos(i->normal.y) * 0.31832);
	// g = open_bmp("./basic/pl.bmp");
	// i->color = set_color(g, i->uv.x, i->uv.y);
	// i->color = new_color(255 * (i->uv.x), 255 * (i->uv.x / i->uv.y), 255 * (i->uv.y));
	i->color = (((int)(i->uv.x * sphere->radius * 4) % 2 == 0 && (int)(i->uv.y * sphere->radius * 2) % 2 != 0) || ((int)(i->uv.x * sphere->radius * 4) % 2 != 0 && (int)(i->uv.y * sphere->radius * 2) % 2 == 0)) ? new_color(255 - sphere->color.r, 255 - sphere->color.g, 255 - sphere->color.b) : sphere->color;
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
