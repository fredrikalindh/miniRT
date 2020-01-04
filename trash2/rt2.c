/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/04 16:11:35 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_iftptr(t_bool (*intersect[5])(t_intersection *, t_ray ray, void *))
{
	intersect[0] = &sp_intersect;
	// intersect[1] = &pl_intersect;
	// intersect[2] = &cy_intersect;
	// intersect[3] = &tr_intersect;
	// intersect[4] = &sq_intersect;
}

void	get_camtoworld()
{
	t_vector forward;
	t_vector right;
	t_vector up;

	forward = normalized(op_min(g_rt.camera->dir, g_rt.camera->position));
	right = cross(vector_xyz(0, -1, 0), forward);
	up = cross(right, forward);
	g_rt.m[0] = right.x;
	g_rt.m[1] = right.y;
	g_rt.m[2] = right.z;
	g_rt.m[3] = up.x;
	g_rt.m[4] = up.y;
	g_rt.m[5] = up.z;
	g_rt.m[6] = forward.x;
	g_rt.m[7] = forward.y;
	g_rt.m[8] = forward.z;
	/// !!!
	int i;
	for (i = 0; i < 9; i++)
		printf("%f\n", g_rt.m[i]);
	// matrix[3][0] = g_rt.camera.origin.x; //necessary ? and use 3X3 ?
	// matrix[3][1] = g_rt.camera.origin.y;
	// matrix[3][2] = g_rt.camera.origin.z;;
}

t_vector	mult_vec_matrix(t_vector src)
{
	t_vector res;

	res.x = src.x * g_rt.m[0] + src.y * g_rt.m[3] + src.z * g_rt.m[6];
	res.y = src.x * g_rt.m[1] + src.y * g_rt.m[4] + src.z * g_rt.m[7];
	res.z = src.x * g_rt.m[2] + src.y * g_rt.m[5] + src.z * g_rt.m[8];
	return (res);
}

t_ray	compute_ray(int pixx, int pixy)
{
	t_ray ray;
	double x;
	double y;
	double r;

	r = g_rt.res_x / g_rt.res_y;
	x = (2 * pixx - 1) * r; // * g_rt.fov
	y = 1 - 2 * pixy; // * g_rt.fov
	ray.origin = g_rt.camera->position; //?
	ray.direction = mult_vec_matrix(vector_xyz(x, y, 0));
	return (ray);
}

t_color ray_cast(t_intersection hit)
{
	return(hit.color);
}

// void	put_pixel(t_color c)
// {
// 	static char *file;
//
// 	file = g_rt.image;
// 	// printf("%d\n", c.b);
// 	file++;
// 	*file++ = (unsigned char)c.b;
// 	*file++ = (unsigned char)c.g;
// 	*file++ = (unsigned char)c.r;
// }

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
	get_camtoworld();
	while (++y < g_rt.res_y)
	{
		x = -1;
		while (++x < g_rt.res_x)
		{
			hit.t = RAY_T_MAX;
			hit.ray = compute_ray((float)x / g_rt.res_x, (float)y / g_rt.res_y);
			// printf("%f %f %f\n", hit.ray.direction.x, hit.ray.direction.y, hit.ray.direction.z);
			hit.color = same_color(0);
			shape = g_rt.shapes;
			while (shape != NULL)
			{
				intersect[shape->id](&hit, hit.ray, shape->shape); //tests if intersection with shape and if so if it's closer than curret t; if if is changes t and shape
				shape = shape->next;
			}
			// hit.color = ray_cast(hit); // gets color from closest shape
			put_pixel(hit.color); //puts into image / file
		}
	}
	return (0);
}
