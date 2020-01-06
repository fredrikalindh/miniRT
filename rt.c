/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/05 23:44:12 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


t_ray	compute_ray(float pixx, float pixy) // use cam struct
{
	t_ray ray;
	double x;
	double y;
	double r;
	t_vector right;
	t_vector up;

	right = cross(vector_xyz(0, 1, 0), g_rt.camera->dir);
	up = cross(g_rt.camera->dir, right);
	r = (float)g_rt.res_x / g_rt.res_y;
	// x = (2 * pixx - 1) * r * tanh((double)g_rt.res_y); // * g_rt.fov
	// y = (1 - 2 * pixy) * tanh((double)g_rt.res_y); // * g_rt.fov
	// x = (2 * pixx - 1) * r * tan((3.141592 * 0.5 * 45) / 180.0); // * g_rt.fov
	// y = (1 - 2 * pixy) * tan((3.141592 * 0.5 * 45) / 180.0); // * g_rt.fov
	x = (2 * pixx - 1) * r * 0.41; // * g_rt.fov
	y = (1 - 2 * pixy) * 0.41; // * g_rt.fov
	// x = (2 * pixx - 1) * r; // * g_rt.fov
	// y = (1 - 2 * pixy) * ; // * g_rt.fov
	ray.direction = normalized(op_add(g_rt.camera->dir, op_add(op_mult_f(right, x), op_mult_f(up, y))));
	ray.origin = g_rt.camera->position; //?
	return (ray);
}

t_color		test(t_color l1, t_color l2, double d, double len)
{
	t_color n;

	len == 0 ? len = 1 : 0;
	n.r = l1.r + l2.r / sqrt(len) * d;
	n.g = l1.g + l2.g / sqrt(len) * d;
	n.b = l1.b + l2.b / sqrt(len) * d;
	return (n);
}

t_color		test2(t_color l, t_color c)
{
	t_color n;

	n.r = ft_min(l.r * c.r / 255, 255);
	n.g = ft_min(l.g * c.g / 255, 255);
	n.b = ft_min(l.b * c.b / 255, 255);
	return (n);
}

t_color ray_cast(t_intersection hit)
{
	t_ray p;
	t_light	*l;
	t_shapes *shape;
	float	d;
	t_color lig;

	l = g_rt.light;
	p.origin = hit.hit;
	lig = test(same_color(0), g_rt.a_light_c, g_rt.a_light_r, 1);
	while (l != NULL)
	{
		p.direction = op_min(l->coor, hit.hit);
		hit.t = normalize(&p.direction);
		d = ft_maxd(0.0, dot(hit.normal, p.direction));
		shape = g_rt.shapes;
		while (shape != NULL)
		{
			if (intersect(&hit, p, shape, 1) && (d = 0.0) == 0.0)
				break ;
			shape = shape->next;
		}
		lig = test(lig, l->color, d * l->bright, hit.t);
		l = l->next;
	}
	return (test2(hit.color, lig));
}

void	put_pixel(t_color c)
{
	unsigned char sum;

	// if (g_rt.save == 1)
	// 	g_rt.image++;
	if (g_rt.filter == 1)
	{
		sum = ft_min((c.b + c.g + c.r), 255);
		*g_rt.image++ = sum * 0.5;
		*g_rt.image++ = sum * 0.8;
		*g_rt.image++ = sum;
	}
	else
	{
		*g_rt.image++ = (unsigned char)c.b;
		*g_rt.image++ = (unsigned char)c.g;
		*g_rt.image++ = (unsigned char)c.r;
	}
	// if (g_rt.save == 0)
		g_rt.image++;
}

int		ray_trace()
{
	int x;
	int y;
	t_intersection hit;
	t_shapes *shape;

	y = -1;
	while (++y < g_rt.res_y)
	{
		x = -1;
		while (++x < g_rt.res_x)
		{
			hit.t = RAY_T_MAX;
			hit.ray = compute_ray((float)x / g_rt.res_x, (float)y / g_rt.res_y);
			shape = g_rt.shapes;
			hit.color = same_color(0);
			while (shape != NULL)
			{
				intersect(&hit, hit.ray, shape, 0);
				shape = shape->next;
			}
			if (hit.t != RAY_T_MAX)
				put_pixel(ray_cast(hit)); // gets color from closest shape
			else
				put_pixel(same_color(0)); //puts into image / file
		}
	}
	return (0);
}
