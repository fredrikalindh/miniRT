/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/10 16:52:03 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

// void		put_pixel(t_color c, int xy)
// {
// 	unsigned char	sum;
//
// 	// printf("[%d] %d %d\n", c.r, c.g, c.b);
// 	if (g_rt.filter != 0)
// 	{
// 		sum = ft_min((c.b + c.g + c.r), 255);
// 		g_rt.image[xy++] = sum * (g_rt.filter % 2); // 1 , 0 , 1
// 		g_rt.image[xy++] = sum * (g_rt.filter / 3); // 0 , 0, 1
// 		g_rt.image[xy++] = sum * ((g_rt.filter + 1) % 2); // 0
// 	}
// 	else
// 	{
// 		g_rt.image[xy++] = (unsigned char)c.b;
// 		g_rt.image[xy++] = (unsigned char)c.g;
// 		g_rt.image[xy++] = (unsigned char)c.r;
// 	}
// 	if (g_rt.save == 0)
// 		g_rt.image[xy++] = 0;
// }

void		put_pixel(t_color c, int xy, char *img)
{
	// unsigned char	sum;

	// printf("[%d] %d %d\n", c.r, c.g, c.b);
	// if (g_rt.filter != 0)
	// {
	// 	sum = ft_min((c.b + c.g + c.r), 255);
	// 	g_rt.image[xy++] = sum * (g_rt.filter % 2); // 1 , 0 , 1
	// 	g_rt.image[xy++] = sum * (g_rt.filter / 3); // 0 , 0, 1
	// 	g_rt.image[xy++] = sum * ((g_rt.filter + 1) % 2); // 0
	// }
	// else
	// {
		img[xy++] = (unsigned char)c.b;
		img[xy++] = (unsigned char)c.g;
		img[xy++] = (unsigned char)c.r;
	// }
	// if (g_rt.save == 0)
		// img[xy++] = 0;
}

typedef struct s_bonus {
	int			x;
	int			max_x;
	int			max_y;
	t_shapes	*shape;
	int			mult;
	char 		*image;
} t_bonus;

void		*trace(void *p)
{
	int				x;
	int				y;
	t_bonus			*b;
	t_intersection	hit;
	t_shapes		*shape;

	b = (t_bonus *)p;
	// printf("%d\n", b->x);
	y = -1;
	while (++y < b->max_y)
	{
		x = b->x;
		while (x < b->max_x)
		{
			hit.t = T_MAX;
			hit.ray = compute_ray((float)x / b->max_x, (float)y / b->max_y);
			shape = b->shape;
			while (shape != NULL)
			{
				intersect(&hit, hit.ray, shape, 0);
				shape = shape->next;
			}
			if (hit.t != T_MAX)
				put_pixel(ray_cast(hit), b->max_x * y * b->mult + x * b->mult, b->image);
			else
				put_pixel(same_color(0), b->max_x * y * b->mult + x * b->mult, b->image);
			x = x + 4;
		}
	}
	return (NULL);
}

int		ray_trace(void)
{
	pthread_t		threads[4];
	t_bonus		*x[4];
	int			i;

	i = -1;
	while (++i < 4)
	{
		x[i] = (t_bonus *)malloc(sizeof(t_bonus));
		x[i]->x = i;
		x[i]->max_x = g_rt.res_x;
		x[i]->max_y = g_rt.res_y;
		x[i]->mult = 4 - g_rt.save;
		x[i]->shape = g_rt.shapes;
		x[i]->image = g_rt.image;
	}
	// trace((void *)x[4]);
	i = -1;
	while (++i < 5)
		pthread_create(&threads[i], NULL, trace, (void *)x[i]);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);
	pthread_join(threads[3], NULL);
	return (1);
}
//
// int		ray_trace(void)
// {
// 	pthread_t		threads[3];
//
// 	// pthread_t		threads;
// 	int *x;
// 	int *y;
// 	int *v;
// 	int *u;
//
// 	x = (int *)malloc(sizeof(int));
// 	y = (int *)malloc(sizeof(int));
// 	v = (int *)malloc(sizeof(int));
// 	u = (int *)malloc(sizeof(int));
// 	*x = 0;
// 	*y = 1;
// 	*v = 2;
// 	*u = 3;
//
//
// 	// one = pthread_create(&threads, NULL, trace, (void *)y);
// 	trace((void *)x);
// 	pthread_create(&threads[0], NULL, trace, (void *)y);
// 	pthread_create(&threads[1], NULL, trace, (void *)v);
// 	pthread_create(&threads[2], NULL, trace, (void *)u);
// 	pthread_join(threads[0], NULL);
// 	pthread_join(threads[1], NULL);
// 	pthread_join(threads[2], NULL);
// 	return (1);
// }
