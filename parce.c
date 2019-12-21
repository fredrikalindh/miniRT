/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:02:57 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/12 22:03:55 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		ft_res(char **split)
{
	int i;

	i = 0;
	g_rt.err = (g_rt.res_x != 0) ? 2 : 0;
	while (split && split[++i] != NULL)
		(is_digit(split[i]) == 0) ? g_rt.err = 1 : 0;
	if (i >= 3)
	{
		g_rt.res_x = ft_min(ft_atoi(split[1]), MAX_X);
		g_rt.res_y = ft_min(ft_atoi(split[2]), MAX_Y);
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	(g_rt.res_x < 0 || g_rt.res_y < 0) ? g_rt.err = 4 : 0;
	if (i < 3 || g_rt.err != 0)
	{
		free(split);
		ft_puterr2('R');
	}
	return (0);
}

int		ft_amb(char **split)
{
	int i;

	i = 0;
	g_rt.err = (g_rt.a_light_r != -1) ? 1 : 0;
	while (split && split[++i] != NULL)
		is_digit(split[i]) == 0 ? g_rt.err = 1 : 0;
	if (i >= 5)
	{
		g_rt.a_light_r = ft_atof(split[1]);
		g_rt.a_light_c = new_color(ft_atoi(split[2]), ft_atoi(split[3]), ft_atoi(split[4]));
		if (outside_range(g_rt.a_light_c))
			g_rt.err = 3;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 4 || g_rt.err != 0)
	{
		free(split);
		ft_puterr2('A');
	}
	return (0);
}

int		ft_cam(char **split)
{
	int i;
	t_camera *new;

	i = 0;
	while (split && split[++i] != NULL)
		is_digit(split[i]) == 0 ? g_rt.err = 1 : 0;
	if (i >= 7)
	{
		if (!(new = (t_camera *)malloc(sizeof(t_camera))))
			return (-1);
		new->next = g_rt.camera;
		new->position = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->dir = vector_xyz(ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6]));
		if (outside_range2(new->dir))
			g_rt.err = 5;
		normalized(new->dir);
		g_rt.camera = new;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 7 || g_rt.err != 0)
		ft_puterr2('c');
	return (0);
}

int		ft_lig(char **split)
{
	int i;
	t_light *new;

	i = 0;
	while (split && split[++i] != NULL)
		is_digit(split[i]) == 0 ? g_rt.err = 1 : 0;
	if (i >= 8)
	{
		if (!(new = (t_light *)malloc(sizeof(t_light))))
			return (-1);
		new->next = g_rt.light;
		new->coor = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->bright = ft_atof(split[4]);
		new->color = new_color(ft_atoi(split[5]), ft_atoi(split[6]), ft_atoi(split[7]));
		if (outside_range(new->color))
			g_rt.err = 3;
		g_rt.light = new;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 8 || g_rt.err != 0)	// free shit == split and cam, light and shapes
		ft_puterr2('l');
	return (0);
}

void	init_ftptr(int (*fill_scene[LIST_SIZE])(char**))
{
	g_rt.camera = NULL;
	g_rt.light = NULL;
	g_rt.shapes = NULL;
	g_rt.a_light_r = -1;
	g_rt.res_x = 0;
	g_rt.line = 0;

	fill_scene[0] = &ft_res;
	fill_scene[1] = &ft_amb;
	fill_scene[2] = &ft_cam;
	fill_scene[3] = &ft_lig;
	fill_scene[4] = &ft_pl;
	fill_scene[5] = &ft_sp;
	fill_scene[6] = &ft_sq;
	fill_scene[7] = &ft_tr;
	fill_scene[8] = &ft_cy;
}
