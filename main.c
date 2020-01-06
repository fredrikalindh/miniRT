/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:28:23 by fredrika          #+#    #+#             */
/*   Updated: 2020/01/06 16:26:41 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_lights()
{
	static t_light	*l = NULL;

	if (l == NULL)
		l = g_rt.light;
	g_rt.to_change.origin = &l->coor;
	g_rt.to_change.dir = NULL;
	g_rt.to_change.r = &l->bright;
	g_rt.to_change.h = NULL;
	l = l->next;
}

static void	rot(double *a, double *b)
{
	double	c;

	c = *a;
	*a = cos(0.1) * *a - sin(0.1) * *b;
	*b = sin(0.1) * c + cos(0.1) * *b;
}

void	move_cam(int x, int y, t_param *p)
{
	int thirdx;
	int thirdy;
	int change;

	change = 0;
	thirdx = g_rt.res_x / 3;
	thirdy = g_rt.res_y / 3;
	if (y < thirdy && (change = 1) == 1)
		rot(&(g_rt.camera->dir.z), &(g_rt.camera->dir.y));
	else if (y > (g_rt.res_y - thirdy) && (change = 1) == 1)
	 	rot(&(g_rt.camera->dir.y), &(g_rt.camera->dir.z));
	if (x < thirdx && (change = 1) == 1)
		rot(&(g_rt.camera->dir.x), &(g_rt.camera->dir.z));
	else if (x > (g_rt.res_x - thirdx) && (change = 1) == 1)
	 	rot(&(g_rt.camera->dir.z), &(g_rt.camera->dir.x));
	if (change == 1)
	{
		g_rt.image = g_rt.or_image;
		ray_trace();
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	}
}

int		deal_mouse(int b, int x, int y, void *p)
{
	t_intersection	hit;
	t_shapes		*shape;
	int				i;
	int				id;

	if (b == 2)
	{
		move_cam(x, y, (t_param *)p);
		return (0);
	}
	hit.ray = compute_ray((float)x / g_rt.res_x, (float)y / g_rt.res_y);
	shape = g_rt.shapes;
	hit.t = T_MAX;
	while (shape != NULL)
	{
		if ((i = intersect(&hit, hit.ray, shape, 0)) > 0)
			id = i;
		shape = shape->next;
	}
	if (hit.t != T_MAX)
	{
		g_rt.to_change.origin = &((t_sphere *)hit.shape)->center;
		g_rt.to_change.dir = (id == 2 || id == 3 || id == 5) ? &((t_plane *)hit.shape)->normal : 0;
		g_rt.to_change.r = (id == 1) ? &((t_sphere *)hit.shape)->radius : 0;
		g_rt.to_change.c3 = (id == 4) ? &((t_triangle *)hit.shape)->c3 : 0;
		if (id == 3 || id == 5)
			g_rt.to_change.r = &((t_cyl *)hit.shape)->r;
		g_rt.to_change.h = (id == 3) ? &((t_cyl *)hit.shape)->h : 0;
	}
	return (0);
}

int		deal_key(int key, void *param)
{
	t_param		*p;
	int			flag;

	p = (t_param *)param;
	if (key == ESC) // exit when esc key c
		exit_program(param);
	if (key == TAB && (flag = 1) == 1)
		g_rt.camera = g_rt.camera->next;
	if ((key == C || key == TAB) && (g_rt.to_change.origin = &g_rt.camera->pos) != NULL)
		g_rt.to_change.dir = &g_rt.camera->dir;
	else if (key == L)
		set_lights();
	else if (key == PLUS || key == MIN || key == H || key == B)
		flag = trans(key);
	else if ((key <= UP && key >= LEFT) || (key >= Q && key <= E) || (key >= A && key <= D) || key == DOT || key == CMA)
		flag = move(g_rt.to_change.origin, g_rt.to_change.dir, key);
	if (flag == 1)
	{
		g_rt.image = g_rt.or_image;
		ray_trace();
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	}
	// printf("%d\n", key);
	return (0);
}

int		main(int ac, char *av[])
{
	t_param		p;

	init_scene(ac, av);
	if (g_rt.save == 1)
	{
		open_image(g_rt.res_x, g_rt.res_y, -1);
		return (0);
	}
	if (!(p.mlx_ptr = mlx_init()))
		return (-1);
	p.bpp = 32;
	p.size_line = g_rt.res_x * 32;
	p.endian = 1;
	p.img_ptr = mlx_new_image(p.mlx_ptr, g_rt.res_x, g_rt.res_y);
	g_rt.or_image = mlx_get_data_addr(p.img_ptr, &p.bpp, &p.size_line, &p.endian); // BITS PER PIZEL & SIZE_LINE & ENDIAN
	g_rt.image = g_rt.or_image;
	g_rt.to_change.origin = &g_rt.camera->pos;
	g_rt.to_change.dir = &g_rt.camera->dir;
	write(1, "\033[1;36mRendering image...\n\033[0m", 30);
	ray_trace();
	p.win_ptr= mlx_new_window(p.mlx_ptr, g_rt.res_x, g_rt.res_y, "miniRT");
	mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img_ptr, 0, 0);
	mlx_key_hook(p.win_ptr, deal_key, (void *)&p);
	mlx_mouse_hook(p.win_ptr, deal_mouse, (void *)&p);
	mlx_hook(p.win_ptr, X_BUTT, 0, exit_program, (void *)&p); // exit when X button
	mlx_loop(p.mlx_ptr);
}
