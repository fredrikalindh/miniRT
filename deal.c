/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:46:03 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/07 16:59:18 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	rerender(t_param *p)
{
	g_rt.image = g_rt.or_image;
	ray_trace();
	mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
}

static void	set_lights(void)
{
	static t_light	*l = NULL;

	if (l == NULL)
		l = g_rt.light;
	g_rt.select.origin = &l->coor;
	g_rt.select.dir = NULL;
	g_rt.select.r = &l->bright;
	g_rt.select.h = NULL;
	l = l->next;
}

void rotcam(int dir)
{
	t_vector up;

	up = cross(g_rt.camera->dir, g_rt.camera->right);
	if (dir == UP)
	{
		g_rt.camera->dir = normalized(op_add(op_mult_f(up, 0.1), g_rt.camera->dir));
	}
	else if (dir == DOWN)
	{
		g_rt.camera->dir = normalized(op_add(op_mult_f(up, -0.1), g_rt.camera->dir));
	}
	else if (dir == LEFT)
	{
		g_rt.camera->dir = normalized(op_add(op_mult_f(g_rt.camera->right, -0.1), g_rt.camera->dir));
		g_rt.camera->right = cross(up, g_rt.camera->dir);
	}
	else
	{
		g_rt.camera->dir = normalized(op_add(op_mult_f(g_rt.camera->right, 0.1), g_rt.camera->dir));
		g_rt.camera->right = cross(up, g_rt.camera->dir);
	}
}

static int	move_cam(int x, int y)
{
	int thirdx;
	int thirdy;
	int change;

	change = 0;
	thirdx = g_rt.res_x / 3;
	thirdy = g_rt.res_y / 3;
	if (y < thirdy && (change = 1) == 1)
		rotcam(UP);
	else if (y > (g_rt.res_y - thirdy) && (change = 1) == 1)
		rotcam(DOWN);
	if (x < thirdx && (change = 1) == 1)
		rotcam(LEFT);
	else if (x > (g_rt.res_x - thirdx) && (change = 1) == 1)
		rotcam(RIGHT);
	return (change);
}
// static int	move_cam(int x, int y)
// {
// 	int thirdx;
// 	int thirdy;
// 	int change;
//
// 	change = 0;
// 	thirdx = g_rt.res_x / 3;
// 	thirdy = g_rt.res_y / 3;
// 	if (y < thirdy && (change = 1) == 1)
// 		rot(&(g_rt.camera->dir.z), &(g_rt.camera->dir.y));
// 	else if (y > (g_rt.res_y - thirdy) && (change = 1) == 1)
// 		rot(&(g_rt.camera->dir.y), &(g_rt.camera->dir.z));
// 	if (x < thirdx && (change = 1) == 1)
// 		rot(&(g_rt.camera->dir.x), &(g_rt.camera->dir.z));
// 	else if (x > (g_rt.res_x - thirdx) && (change = 1) == 1)
// 		rot(&(g_rt.camera->dir.z), &(g_rt.camera->dir.x));
// 	return (change);
// }

static void	select_object(int x, int y, int i, int id)
{
	t_intersection	hit;
	t_shapes		*shape;

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
		g_rt.select.origin = &((t_sphere *)hit.shape)->center;
		g_rt.select.dir = (id == 2 || id == 3 || id == 5) ?
		&((t_plane *)hit.shape)->normal : 0;
		g_rt.select.r = (id == 1) ? &((t_sphere *)hit.shape)->radius : 0;
		g_rt.select.c3 = (id == 4) ? &((t_triangle *)hit.shape)->c3 : 0;
		if (id == 3 || id == 5)
			g_rt.select.r = &((t_cyl *)hit.shape)->r;
		g_rt.select.h = (id == 3) ? &((t_cyl *)hit.shape)->h : 0;
	}
}

int			deal_mouse(int b, int x, int y, void *p)
{
	// printf("%d\n", b);
	if (b == 4 && g_rt.camera->fov < 177)
		g_rt.camera->fov += 3;
	else if (b == 5 && g_rt.camera->fov > 3)
		g_rt.camera->fov -= 3;
	else if (b == 7)
		g_rt.filter++;
	else if (b == 6)
		g_rt.filter--;
	else if (b == 2 && move_cam(x, y) == 1)
		;
	else if (b == 1)
	{
		select_object(x, y, 0, 0);
		return (1);
	}
	else
		return (1);
	rerender((t_param *)p);
	return (0);
}

int			deal_key(int key, void *p)
{
	int			flag;

	if (key == ESC)
		exit_program(p);
	if (key == TAB && (flag = 1) == 1)
		g_rt.camera = g_rt.camera->next;
	if ((key == C || key == TAB) && (g_rt.select.origin = &g_rt.camera->pos))
		g_rt.select.dir = &g_rt.camera->dir;
	else if (key == L)
		set_lights();
	else if (key == PLUS || key == MIN || key == H || key == B)
		flag = trans(key);
	else if (key <= UP && key >= LEFT && g_rt.select.dir == &g_rt.camera->dir)
		rotcam(key);
	else if ((key <= UP && key >= LEFT) || (key >= Q && key <= E) ||
	(key >= A && key <= D) || key == DOT || key == CMA)
		flag = move(g_rt.select.origin, g_rt.select.dir, key);
	if (flag == 1)
		rerender(p);
	return (0);
}
