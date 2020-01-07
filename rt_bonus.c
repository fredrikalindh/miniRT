/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/07 13:45:50 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <pthread.h>

t_ray		compute_ray(float pixx, float pixy)
{
	t_ray			ray;
	double			x;
	double			y;
	t_vector		right;
	t_vector		up;

	if (fabs(g_rt.camera->dir.y) > 0.8)
		right = cross(vector_xyz(0, 0, 1), g_rt.camera->dir);
	else
		right = cross(vector_xyz(0, 1, 0), g_rt.camera->dir);
	up = cross(g_rt.camera->dir, right);
	x = (2 * pixx - 1) * (float)g_rt.res_x / g_rt.res_y * 0.41; // * g_rt.fov
	y = (1 - 2 * pixy) * 0.41; // * g_rt.fov
	ray.dir = normalized(op_add(g_rt.camera->dir,
		op_add(op_mult_f(right, x), op_mult_f(up, y))));
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
	int				i;

	i = (g_rt.save == 1) ? xy * 3 : xy * 4;
	// g_rt.image = g_rt.or_image + i;
	if (g_rt.filter == 1)
	{
		sum = ft_min((c.b + c.g + c.r), 255);
		g_rt.image[i++] = sum * (g_rt.filter);
		g_rt.image[i++] = sum * (g_rt.filter);
		g_rt.image[i++] = sum * (g_rt.filter);
	}
	else
	{
		printf("?\n");
		*g_rt.image = (unsigned char)c.b;
		printf("??\n");
		*g_rt.image++ = (unsigned char)c.g;
		*g_rt.image++ = (unsigned char)c.r;
	}
	if (g_rt.save == 0)
		*g_rt.image++ = 0;
	printf("PP%d\n", xy);
}

void *trace(void *y)
{
	t_intersection	*hit;
	t_shapes		*shape;
	int				xy;

	hit = (t_intersection *)y;
	xy = hit->t;
	hit->t = T_MAX;
	shape = g_rt.shapes;
	while (shape != NULL)
	{
		intersect(hit, hit->ray, shape, 0);
		shape = shape->next;
	}
	printf("%d\n", xy);
	if (hit->t != T_MAX)
		put_pixel(ray_cast(*hit), xy);
	else
		put_pixel(same_color(0), xy);
	return (NULL);
}

int			ray_trace(void)
{
	int				x;
	int				y;
	t_intersection	*hit;
	pthread_t		threads[2];

	y = -1;
	while (++y < g_rt.res_y)
	{
		x = -1;
		while (++x < g_rt.res_x)
		{
			hit->t = x * y;
			hit->ray = compute_ray((float)x / g_rt.res_x, (float)y / g_rt.res_y);
			if (x % 3 == 0)
				trace((void *)&hit);
			else if (x % 3 == 1)
			{
				printf("%d\n", x);
				pthread_create(&threads[0], NULL, trace, (void *)&hit);
				pthread_join(threads[0], NULL);
			}
			else
			{
				printf("%d\n", x);
				pthread_create(&threads[1], NULL, trace, (void *)&hit);
				pthread_join(threads[1], NULL);
			}
		}
	}
	return (0);
}
