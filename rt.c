/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/03 15:57:35 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_iftptr(t_bool (*intersect[5])(t_ray, t_intersection *))
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
	right = cross(vector_xyz(0, 1, 0), forward);
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
	ray.tMax = RAY_T_MAX;
	return (ray);
}

int		ray_trace()
{
	int x;
	int y;
	t_ray shoot;
	t_intersection hit;
	t_bool (*intersect[5])(t_ray, t_intersection *);

	y = -1;
	init_iftptr(intersect);
	get_camtoworld();
	while (++y <= g_rt.res_y)
	{
		x = -1;
		while (++x <= g_rt.res_x)
		{
			hit.t = RAY_T_MAX;
			shoot = compute_ray(x, y);
			while (g_rt.shapes != NULL)
				intersect[g_rt.shapes->id](shoot, &hit); //tests if intersection with shape and if so if it's closer than curret t; if if is changes t and shape
		//	hit.color = ray_cast(shoot, hit); // gets color from closest shape
		//	put_pixel(hit.color); //puts into image / file
		}
	}
	return (0);
}
