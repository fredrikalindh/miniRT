/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/19 13:32:38 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <pthread.h>
#define THREADS 4

void		*trace(void *p)
{
	int				x;
	int				y;
	int				m;
	t_intersection	hit;
	t_shapes		*shape;

	y = -1;
	m = (g_rt.save == 1) ? 3 : 4;
	while (++y < g_rt.res_y & (x = *((int *)p)) >= 0)
	{
		while (x < g_rt.res_x && (hit.t = T_MAX) == T_MAX)
		{
			hit.ray = compute_ray((float)x / g_rt.res_x, (float)y / g_rt.res_y);
			shape = g_rt.shapes;
			while (shape != NULL && intersect(&hit, hit.ray, shape, 0) >= 0)
				shape = shape->next;
			(hit.t != T_MAX) ? put_pixel(ray_cast(hit), g_rt.res_x * y * m +
			x * m) : put_pixel(same_color(0), g_rt.res_x * y * m + x * m);
			x = x + THREADS;
		}
	}
	return (NULL);
}

int			ray_trace(void)
{
	pthread_t		threads[THREADS];
	int				x[THREADS];
	int				i;

	i = -1;
	while (++i < THREADS)
		x[i] = i;
	i = -1;
	while (++i < THREADS)
		pthread_create(&threads[i], NULL, trace, (void *)&x[i]);
	i = -1;
	while (++i < THREADS)
		pthread_join(threads[i], NULL);
	return (1);
}
