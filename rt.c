/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/10 21:39:05 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_iftptr(t_bool (*intersect[5])(t_intersection *, t_ray ray, void *))
{
	intersect[0] = &sp_intersect;
	intersect[1] = &pl_intersect;
	// intersect[2] = &cy_intersect;
	intersect[3] = &tr_intersect;
	// intersect[4] = &sq_intersect;
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
	// x = (2 * pixx - 1) * r * tanh((float)g_rt.res_y); // * g_rt.fov
	// y = (1 - 2 * pixy) * tanh((float)g_rt.res_y); // * g_rt.fov
	x = (2 * pixx - 1) * r * tan(0.5); // * g_rt.fov
	y = (1 - 2 * pixy) * tan(0.5); // * g_rt.fov
	// x = (2 * pixx - 1) * r * cos(1); // * g_rt.fov
	// y = (1 - 2 * pixy) * cos(1); // * g_rt.fov
	// dprintf(fd, "%f %f\n", x, y);
	ray.direction = normalized(op_add(g_rt.camera->dir, op_add(op_mult_f(right, x), op_mult_f(up, y))));
	// printf("D %f %f %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
	ray.origin = g_rt.camera->position; //?
	return (ray);
}

t_color ray_cast(t_intersection hit)
{
	// s_ray p;
	// t_light	*l;
	// t_shapes *shape;
	// t_color lcol;
	// t_bool (*intersect[5])(t_intersection *, t_ray, void *);
	//
	// p.origin = op_add(hit.ray.origin, op_mult_f(hit.ray.direction, hit.t));
	// l = g_rt.light;
	// while (l != NULL)
	// {
	// 	hit.t = RAY_T_MAX;
	// 	p.direction = op_min(l->coor, p);
	// 	shape = g_rt.shapes;
	// 	if (dot(hit.normal, p.direction) > 0.0)
	// 	{
	// 		while (shape != NULL && hit.t == RAY_T_MAX)
	// 		{
	// 			if (shape->shape != hit.shape)
	// 				intersect[shape->id](&hit, p, shape->shape);
	// 			shape = shape->next;
	// 		}
	// 		if (hit.t == RAY_T_MAX)
	// 			lcol = color_add(lcol, color_mult(l->color, l->bright));
	// 	}
	// 	l = l->next;
	// }
	return(hit.color);
}

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
			hit.color = same_color(0);
			shape = g_rt.shapes;
			while (shape != NULL)
			{
				intersect[shape->id](&hit, hit.ray, shape->shape);
				shape = shape->next;
			}
			// hit.color = ray_cast(hit); // gets color from closest shape
			put_pixel(hit.color); //puts into image / file
		}
	}
	return (0);
}
