/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/04 19:53:02 by frlindh          ###   ########.fr       */
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
	t_vector forward;
	t_vector right;
	t_vector up;
	// int fd = open("./xy.tx", O_WRONLY, O_APPEND);

	forward = normalized(op_min(g_rt.camera->dir, g_rt.camera->position));
	right = cross(vector_xyz(0, 1, 0), forward);
	up = cross(right, forward);
	// double fov;
	//
	// fov = tan(g_rt.res_y / 2);
	r = (float)g_rt.res_x / g_rt.res_y;
	x = (2 * pixx - 1) * r; // * g_rt.fov
	y = 1 - 2 * pixy; // * g_rt.fov
	// dprintf(fd, "%f %f\n", x, y);
	ray.direction = op_add(forward, op_add(op_mult_f(right, x), op_mult_f(up, y)));
	ray.origin = g_rt.camera->position; //?
	return (ray);
}

t_color ray_cast(t_intersection hit)
{
	apply_gamma(&g_rt.a_light_c, g_rt.a_light_r, 1);
	return(color_add(hit.color, g_rt.a_light_c));
}

void	put_pixel(t_color c)
{
	*g_rt.image++ = (unsigned char)c.b;
	*g_rt.image++ = (unsigned char)c.g;
	*g_rt.image++ = (unsigned char)c.r;
	g_rt.image++;
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
	// get_camtoworld();
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
			hit.color = ray_cast(hit); // gets color from closest shape
			put_pixel(hit.color); //puts into image / file
		}
	}
	return (0);
}
