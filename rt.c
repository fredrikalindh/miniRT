/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/21 18:14:59 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_iftptr(t_bool (*intersect[5])(t_intersection *, t_ray ray, void *))
{
	intersect[0] = &sp_intersect;
	intersect[1] = &pl_intersect;
	intersect[2] = &cy_intersect;
	intersect[3] = &tr_intersect;
	intersect[4] = &sq_intersect;
}

t_ray	compute_ray(float pixx, float pixy) // use cam struct
{
	t_ray ray;
	double x;
	double y;
	double r;
	t_vector right;
	t_vector up;
	// int fd = open("./rays.txt", O_WRONLY, O_APPEND);

	right = cross(vector_xyz(0, 1, 0), g_rt.camera->dir);
	up = cross(g_rt.camera->dir, right);
	// double fov;
	//
	// fov = tan(g_rt.res_y / 2);
	r = (float)g_rt.res_x / g_rt.res_y;
	// x = (2 * pixx - 1) * r * tanh((double)g_rt.res_y); // * g_rt.fov
	// y = (1 - 2 * pixy) * tanh((double)g_rt.res_y); // * g_rt.fov
	x = (2 * pixx - 1) * r * tan((3.141592 * 0.5 * 45) / 180.0); // * g_rt.fov
	y = (1 - 2 * pixy) * tan((3.141592 * 0.5 * 45) / 180.0); // * g_rt.fov
	// x = (2 * pixx - 1) * r; // * g_rt.fov
	// y = (1 - 2 * pixy) * ; // * g_rt.fov
	// dprintf(fd, "%f %f\n", x, y);
	ray.direction = normalized(op_add(g_rt.camera->dir, op_add(op_mult_f(right, x), op_mult_f(up, y))));
	ray.origin = g_rt.camera->position; //?
	return (ray);
}

t_color		test(t_color c, t_color l, double d)
{
	t_color n;

	n.r = c.r * l.r / 255 * d;
	n.g = c.g * l.g / 255 * d;
	n.b = c.b * l.b / 255 * d;
	return (n);
}

t_bool			ft_hit(t_ray ray, void *shape)
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
	if (!(t > RAY_T_MIN && t < RAY_T_MAX))
		t = (-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a);
	if (t > RAY_T_MIN && t < RAY_T_MAX)
		return (TRUE);
	return (FALSE);
}


t_color ray_cast(t_intersection hit)
{
	t_ray p;
	t_light	*l;
	t_shapes *shape;
	float	d;

	l = g_rt.light;
	p.direction = normalized(op_min(l->coor, hit.hit));
	p.origin = hit.hit;
	hit.t = RAY_T_MAX;
	d = dot(hit.normal, p.direction);
	if (d < 0.0)
		d = 0.0;
	shape = g_rt.shapes;
	while (shape != NULL && hit.t == RAY_T_MAX)
	{
		if (shape->shape != hit.shape && ft_hit(p, shape->shape))
		{
			d = 0.0;
			break ;
		}
		shape = shape->next;
	}
	return(test(hit.color, l->color, d));
}

// t_color ray_cast(t_intersection hit)
// {
// 	t_ray p;
// 	t_light	*l;
// 	t_shapes *shape;
// 	float	d;
// 	t_bool (*intersect[5])(t_intersection *, t_ray, void *);
// 	int flag;
//
// 	l = g_rt.light;
// 	init_iftptr(intersect);
// 	d = 0.0;
// 	while (l != NULL)
// 	{
// 		p.direction = normalized(op_min(l->coor, hit.hit));
// 		shape = g_rt.shapes;
// 		flag = 0;
// 		while (shape != NULL)
// 		{
// 			if (shape->shape != hit.shape && intersect[shape->id](&hit, p, shape->shape))
// 			{
// 				flag = 1;
// 				break ;
// 			}
// 			shape = shape->next;
// 		}
// 		if (flag == 0)
// 			d += dot(hit.normal, p.direction);
// 		d = ft_mind(ft_maxd(d, 1), 0);
// 		hit.color = test(hit.color, l->color, d);
// 		l = l->next;
// 	}
// 	return(hit.color);
// }

void	put_pixel(t_color c)
{
	// if (g_rt.save == 1)
	// 	g_rt.image++;
	*g_rt.image++ = (unsigned char)c.b;
	*g_rt.image++ = (unsigned char)c.g;
	*g_rt.image++ = (unsigned char)c.r;
	// if (g_rt.save == 0)
		g_rt.image++;
	// g_rt.image += 4;
}

int		ray_trace()
{
	int x;
	int y;
	t_intersection hit;
	t_bool (*intersect[5])(t_intersection *, t_ray, void *);
	t_shapes *shape;

	y = -1;
	init_iftptr(intersect);
	while (++y < g_rt.res_y)
	{
		x = -1;
		while (++x < g_rt.res_x)
		{
			hit.t = RAY_T_MAX;
			hit.ray = compute_ray((float)x / g_rt.res_x, (float)y / g_rt.res_y);
			shape = g_rt.shapes;
			while (shape != NULL)
			{
				intersect[shape->id](&hit, hit.ray, shape->shape);
				shape = shape->next;
			}
			if (hit.t != RAY_T_MAX)
				put_pixel(ray_cast(hit)); // gets color from closest shape
			else
				put_pixel(same_color(0.0)); //puts into image / file
		}
	}
	return (0);
}
