/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/02 16:48:18 by frlindh          ###   ########.fr       */
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

t_ray	compute_ray(int x, int y)
{
	t_ray ray;
	double w;
	double h;

	w = g_rt.res_x / 2 - x;
	h = g_rt.res_y / 2 - y;
	ray.origin = g_rt->camera.position; //?
	ray.direction = vector_xyz(g_rt->camera.dir);
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
			hit.color = same_color(0); // sets color to black
			shoot = compute_ray(x, y);
			while (g_rt.shapes != NULL)
				intersect[g_rt.shapes.id](shoot, &hit); //tests if intersection with shape and if so if it's closer than curret t; if if is changes t and shape
			if (hit.t != RAY_T_MAX)
				get_color(shoot, &hit); // gets color from closest shape
			put_pixel(hit.color); //puts into image / file
		}
	}
}
