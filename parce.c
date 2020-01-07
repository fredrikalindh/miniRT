/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:02:57 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/07 14:44:12 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			ft_res(char **s, int i)
{
	g_rt.err = (g_rt.res_x != 0) ? 2 : 0;
	if (i == 3)
	{
		g_rt.res_x = ft_min(ft_atoi(s[1]), MAX_X);
		g_rt.res_y = ft_min(ft_atoi(s[2]), MAX_Y);
	}
	i = -1;
	while (s && s[++i] != NULL)
		free(s[i]);
	(g_rt.res_x < 0 || g_rt.res_y < 0) ? g_rt.err = 4 : 0;
	if (i != 3 || g_rt.err != 0)
	{
		free(s);
		ft_puterr2('R');
	}
	return (0);
}

int			ft_amb(char **s, int i)
{
	g_rt.err = (g_rt.a_light_r != -1) ? 2 : 0;
	if (i == 5)
	{
		g_rt.a_light_r = ft_atof(s[1]);
		g_rt.a_light_c = new_color(ft_atoi(s[2]), ft_atoi(s[3]), ft_atoi(s[4]));
		if (outside_range(g_rt.a_light_c))
			g_rt.err = 3;
	}
	i = -1;
	while (s && s[++i] != NULL)
		free(s[i]);
	if (i != 5 || g_rt.err != 0)
	{
		free(s);
		ft_puterr2('A');
	}
	return (0);
}

static void	circle(t_camera *new, t_camera *parce)
{
	if (g_rt.camera != NULL)
	{
		while (parce && parce->next != NULL)
			parce = parce->next;
		parce->next = new;
	}
	else
		g_rt.camera = new;
}

int			ft_cam(char **s, int i)
{
	t_camera	*new;

	if (i == 8)
	{
		if (!(new = (t_camera *)malloc(sizeof(t_camera))))
			return (-1);
		new->pos = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->dir =
		normalized(vector_xyz(ft_atof(s[4]), ft_atof(s[5]), ft_atof(s[6])));
		if (outside_range2(new->dir))
			g_rt.err = 5;
		new->right = (fabs(new->dir.y) > fabs(new->dir.x)) ?
		cross(vector_xyz(0, 0, -1), new->dir):
		cross(vector_xyz(0, 1, 0), new->dir);
		if ((new->fov = ft_atoi(s[7])) < 0 ||  new->fov > 180)
			g_rt.err = 5;
		new->next = NULL;
		circle(new, g_rt.camera);
	}
	i = -1;
	while (s && s[++i] != NULL)
		free(s[i]);
	if (i != 8 || g_rt.err != 0)
		ft_puterr2('C');
	return (0);
}

int			ft_lig(char **s, int i)
{
	t_light		*new;

	if (i == 8)
	{
		if (!(new = (t_light *)malloc(sizeof(t_light))))
			return (-1);
		new->next = g_rt.light;
		new->coor = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->bright = ft_atof(s[4]);
		new->color = new_color(ft_atoi(s[5]), ft_atoi(s[6]), ft_atoi(s[7]));
		if (outside_range(new->color))
			g_rt.err = 3;
		g_rt.light = new;
	}
	i = -1;
	while (s && s[++i] != NULL)
		free(s[i]);
	if (i != 8 || g_rt.err != 0)
		ft_puterr2('l');
	return (0);
}
