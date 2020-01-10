/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/10 18:56:06 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <pthread.h>
#define THREADS 16

t_ray		compute_ray(float pixx, float pixy)
{
	t_ray			ray;
	double			x;
	double			y;
	t_vector		up;

	up = cross(g_rt.camera->dir, g_rt.camera->right);
	y = (1 - 2 * pixy) * atan(g_rt.camera->fov * 0.0087) ;
	x = (2 * pixx - 1) * atan(g_rt.camera->fov * 0.0087) *
	((float)g_rt.res_x / g_rt.res_y);
	ray.dir = normalized(op_add(g_rt.camera->dir,
		op_add(op_mult_f(g_rt.camera->right, x), op_mult_f(up, y))));
	ray.origin = g_rt.camera->pos;
	return (ray);
}

t_color		ray_cast(t_intersection hit)
{
	t_ray			p;
	t_light			*l;
	t_shapes		*shape;
	float			d;
	t_color			lig;

	l = g_rt.light;
	p.origin = hit.hit;
	lig = light_color(same_color(0), g_rt.a_light_c, g_rt.a_light_r, 1);
	while (l != NULL)
	{
		p.dir = op_min(l->coor, hit.hit);
		hit.t = normalize(&p.dir);
		d = ft_maxd(0.0, dot(hit.normal, p.dir));
		shape = g_rt.shapes;
		while (shape != NULL)
		{
			if (intersect(&hit, p, shape, 1) && (d = 0.0) == 0.0)
				break ;
			shape = shape->next;
		}
		lig = light_color(lig, l->color, d * l->bright, hit.t);
		l = l->next;
	}
	return (total_color(hit.color, lig));
}

void		put_pixel(t_color c, int xy)
{
	unsigned char	sum;

	if (g_rt.filter != 0)
	{
		sum = ft_min((c.b + c.g + c.r), 255);
		g_rt.image[xy++] = sum * (g_rt.filter % 2); // 1 , 0 , 1
		g_rt.image[xy++] = sum * (g_rt.filter / 3); // 0 , 0, 1
		g_rt.image[xy++] = sum * ((g_rt.filter + 1) % 2); // 0
	}
	else
	{
		g_rt.image[xy++] = (unsigned char)c.b;
		g_rt.image[xy++] = (unsigned char)c.g;
		g_rt.image[xy++] = (unsigned char)c.r;
	}
	if (g_rt.save == 0)
		g_rt.image[xy++] = 0;
}

void		*trace(void *p)
{
	int				x;
	int				y;
	int				mult;
	t_intersection	hit;
	t_shapes		*shape;

	y = -1;
	mult = (g_rt.save == 1) ? 3 : 4;
	while (++y < g_rt.res_y & (x = *((int *)p)) >= 0)
	{

		while (x < g_rt.res_x && (hit.t = T_MAX) == T_MAX)
		{
			hit.ray = compute_ray((float)x / g_rt.res_x, (float)y / g_rt.res_y);
			shape = g_rt.shapes;
			while (shape != NULL && intersect(&hit, hit.ray, shape, 0) >= 0)
				shape = shape->next;
			if (hit.t != T_MAX)
				put_pixel(ray_cast(hit), g_rt.res_x * y * mult + x * mult);
			else
				put_pixel(same_color(0), g_rt.res_x * y * mult + x * mult);
			x = x + THREADS;
		}
	}
	return (NULL);
}

int		ray_trace(void)
{
	pthread_t	threads[THREADS];
	int			x[THREADS];
	int			i;

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
