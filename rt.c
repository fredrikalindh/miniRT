/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/03 12:34:33 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	(*intersect[5])(t_ray, t_intersection *);
{
	intersect[0] = &sp_intersect;
	intersect[1] = &pl_intersect;
	intersect[2] = &cy_intersect;
	intersect[3] = &tr_intersect;
	intersect[4] = &sq_intersect;
}

double	**get_camtoworld()
{
	double[4][4] matrix;
	t_vector forward;
	t_vector right;
	t_vector up;

	forward = normalize(op_min(g_rt.camera.dir, g_rt.camera.origin));
	right = cross(vector_xyz(0, 1, 0), forward);
	up = cross(right, forward);
	matrix[0][0] = right.x;
	matrix[0][1] = right.y;
	matrix[0][2] = right.z;
	matrix[1][0] = up.x;
	matrix[1][1] = up.y;
	matrix[1][2] = up.z;
	matrix[2][0] = forward.x;
	matrix[2][1] = forward.y;
	matrix[2][2] = forward.z;
	matrix[3][0] = g_rt.camera.origin.x;
	matrix[3][1] = g_rt.camera.origin.y;
	matrix[3][2] = g_rt.camera.origin.z;
	return (matrix);
}

t_ray	compute_ray(int pixx, int pixy)
{
	t_ray ray;
	double x;
	double y;
	double r;
	double **matrix;

	r = g_rt.res_x / g_rt.res_y;
	x = (2 * pixx - 1) * r; // * g_rt.fov
	y = 1 - 2 * pixy; // * g_rt.fov
	matrix = get_camtoworld();
	ray.origin = g_rt->camera.position; //?
	ray.direction = mult_vec_matrix(matrix, vector_xyz(x, y, 0));
	return (ray);
}

PointOnTheRay = op_add(origin + op_mulf_f(dir, t));

int		ray_trace()
{
	int x;
	int y;
	t_ray shoot;
	t_intersection hit;
	t_bool (*intersect[5])(t_ray, t_intersection *);

	y = -1;
	init_iftptr();
	while (++y <= g_rt.res_y)
	{
		x = -1;
		while (++x <= g_rt.res_x)
		{
			hit.t = RAY_T_MAX;
			shoot = compute_ray(x, y);
			while (g_rt.shapes != NULL)
				intersect[g_rt.shapes.id](shoot, &hit); //tests if intersection with shape and if so if it's closer than curret t; if if is changes t and shape
			hit.color = ray_cast(shoot, hit); // gets color from closest shape
			put_pixel(hit.color); //puts into image / file
		}
	}
}
