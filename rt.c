/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/01 18:56:09 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	compute_ray(int x, int y)
{
	t_ray ray;
	double w;
	double h;

	w = g_rt.res_x / 2 - x;
	h = g_rt.res_y / 2 - y;
	ray.origin = g_rt.camera.position; //?
	ray.direction = sinh(sqrt(w * w + h * h));
}

int		ray_trace()
{
	int x;
	int y;
	t_ray shoot;
	t_intersection hit;

	y = -1;
	while (++y <= g_rt.res_y)
	{
		x = -1;
		while (++x <= g_rt.res_x)
		{
			hit.t = RAY_T_MAX;
			hit.color = same_color(0); // sets color to black
			shoot = compute_ray(x, y);
			while (g_rt.shapes != NULL)
				intersect[g_rt.shapes.id](shoot, &hit); //gets the closest shape
			if (hit.t != RAY_T_MAX)
				get_color(shoot, &hit); // gets color from closest shape
			put_pixel(hit.color); //puts into image / file
		}
	}
}
