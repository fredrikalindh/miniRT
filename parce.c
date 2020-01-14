/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:02:57 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/14 14:00:48 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int			ft_res(char **s, int i, int j)
{
	g_rt.err = (g_rt.res_x != 0) ? 2 : 0;
	if (i == 3)
	{
		g_rt.res_x = ft_min(ft_atoi(s[1]), MAX_X);
		g_rt.res_y = ft_min(ft_atoi(s[2]), MAX_Y);
	}
	while (s && s[++j] != NULL)
		free(s[j]);
	(g_rt.res_x < 0 || g_rt.res_y < 0) ? g_rt.err = 4 : 0;
	if (j != 3 || g_rt.err != 0)
	{
		free(s);
		ft_puterr2('R');
	}
	return (0);
}

int			ft_amb(char **s, int i, int j)
{
	g_rt.err = (g_rt.a_light_r != -1) ? 2 : 0;
	if (i == 5)
	{
		g_rt.a_light_r = ft_atof(s[1]);
		g_rt.a_light_c = new_color(ft_atoi(s[2]), ft_atoi(s[3]), ft_atoi(s[4]));
		if (col_range(g_rt.a_light_c) || f_range(g_rt.a_light_r))
			g_rt.err = 3;
	}
	while (s && s[++j] != NULL)
		free(s[j]);
	if (j != 5 || g_rt.err != 0)
	{
		free(s);
		ft_puterr2('A');
	}
	return (0);
}

static void	add_back(t_camera *new, t_camera *parce)
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

int			ft_cam(char **s, int i, int j)
{
	t_camera	*new;

	if (i == 8)
	{
		if (!(new = (t_camera *)malloc(sizeof(t_camera))))
			return (-1);
		new->pos = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->dir =
		normalized(vector_xyz(ft_atof(s[4]), ft_atof(s[5]), ft_atof(s[6])));
		(v_range(new->dir)) ? g_rt.err = 5 : 0;
		new->right = (fabs(new->dir.y) > 0.7) ?
		cross(vector_xyz(0, 0, -1), new->dir) :
		cross(vector_xyz(0, 1, 0), new->dir);
		if ((new->fov = ft_atoi(s[7])) < 0 || new->fov > 180)
			g_rt.err = 6;
		new->next = NULL;
		add_back(new, g_rt.camera);
	}
	while (s && s[++j] != NULL)
		free(s[j]);
	if (j != 8 || g_rt.err != 0)
		ft_puterr2('C');
	return (0);
}

int			ft_lig(char **s, int i, int j)
{
	t_light		*new;

	if (i == 8)
	{
		if (!(new = (t_light *)malloc(sizeof(t_light))))
			return (-1);
		new->next = (s[0][0] == 'l') ? g_rt.light : g_rt.d_light;
		new->coor = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->bright = ft_atof(s[4]);
		new->color = new_color(ft_atoi(s[5]), ft_atoi(s[6]), ft_atoi(s[7]));
		if (col_range(new->color) || f_range(new->bright))
			g_rt.err = 3;
		if (s[0][0] == 'l')
			g_rt.light = new;
		else
			g_rt.d_light = new;
	}
	while (s && s[++j] != NULL)
		free(s[j]);
	if (j != 8 || g_rt.err != 0)
		ft_puterr2('l');
	return (0);
}
