/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:02:13 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/13 17:04:49 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray		compute_ray(float pixx, float pixy)
{
	t_ray			ray;
	double			x;
	double			y;
	t_vector		up;

	up = cross(g_rt.camera->dir, g_rt.camera->right);
	y = (1 - 2 * pixy) * tan(g_rt.camera->fov * 0.0087266);
	x = ((2 * pixx - 1) * ((float)g_rt.res_x / g_rt.res_y)) *
	tan(g_rt.camera->fov * 0.0087266);
	ray.dir = normalized(op_add(g_rt.camera->dir,
		op_add(op_mult_f(g_rt.camera->right, x), op_mult_f(up, y))));
	ray.origin = g_rt.camera->pos;
	return (ray);
}

t_color		get_dl(t_intersection hit)
{
	t_ray			p;
	t_light			*l;
	t_shapes		*shape;
	float			d;
	t_color			lig;

	l = g_rt.d_light;
	p.origin = hit.hit;
	lig = same_color(0.0);
	while (l != NULL)
	{
		p.dir = normalized(op_mult_f(l->coor, -1));
		hit.t = T_MAX;
		d = ft_maxd(0.0, dot(hit.normal, p.dir));
		shape = g_rt.shapes;
		while (shape != NULL)
		{
			if (intersect(&hit, p, shape, 1) && (d = 0.0) == 0.0)
				break ;
			shape = shape->next;
		}
		lig = light_color(lig, l->color, d * l->bright, 1);
		l = l->next;
	}
	return (lig);
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
	lig = light_color(get_dl(hit), g_rt.a_light_c, g_rt.a_light_r, 1);
	while (l != NULL)
	{
		p.dir = op_min(l->coor, hit.hit);
		hit.t = normalize(&p.dir) + EPSILON;
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
		g_rt.image[xy++] = sum * (g_rt.filter % 2);
		g_rt.image[xy++] = sum * (g_rt.filter / 3);
		g_rt.image[xy++] = sum * ((g_rt.filter + 1) % 2);
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
