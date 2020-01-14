/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:06:12 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/14 14:00:07 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		ft_pl(char **s, int i, int j)
{
	t_plane		*new;
	t_shapes	*shell;

	if (i == 10 || (g_rt.err = -1) != -1)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))) ||
		!(new = (t_plane *)malloc(sizeof(t_plane))))
			return (-1);
		shell->next = g_rt.shapes;
		new->pos = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->normal = vector_xyz(ft_atof(s[4]), ft_atof(s[5]), ft_atof(s[6]));
		v_range(new->normal) ? g_rt.err = 5 : normalize(&new->normal);
		new->color = new_color(ft_atoi(s[7]), ft_atoi(s[8]), ft_atoi(s[9]));
		(col_range(new->color)) ? g_rt.err = 3 : 0;
		new->check = (s[10] != NULL) ? 1 : 0;
		shell->shape = (void *)new;
		shell->id = pl;
		g_rt.shapes = (void *)shell;
	}
	while (s && s[++j] != NULL)
		free(s[j]);
	if (g_rt.err != 0 || j > 11)
		ft_puterr2('p');
	return (0);
}

int		ft_sp(char **s, int i, int j)
{
	t_sphere	*new;
	t_shapes	*shell;

	if (i == 8 || (g_rt.err = -1) != -1)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))) ||
		!(new = (t_sphere *)malloc(sizeof(t_sphere))))
			return (-1);
		shell->next = g_rt.shapes;
		new->center = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->radius = ft_atof(s[4]) / 2;
		new->color = new_color(ft_atoi(s[5]), ft_atoi(s[6]), ft_atoi(s[7]));
		(col_range(new->color) || new->radius < 0) ? g_rt.err = 3 : 0;
		new->check = (s[8] != NULL) ? 1 : 0;
		shell->shape = (void *)new;
		shell->id = sp;
		g_rt.shapes = (void *)shell;
	}
	while (s && s[++j] != NULL)
		free(s[j]);
	if (g_rt.err != 0 || j > 9)
		ft_puterr2('h');
	return (0);
}

int		ft_sq(char **s, int i, int j)
{
	t_square	*new;
	t_shapes	*shell;

	if (i == 11 || (g_rt.err = -1) != -1)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))) ||
		!(new = (t_square *)malloc(sizeof(t_square))))
			return (-1);
		shell->next = g_rt.shapes;
		new->center = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->normal = vector_xyz(ft_atof(s[4]), ft_atof(s[5]), ft_atof(s[6]));
		v_range(new->normal) ? g_rt.err = 5 : normalize(&new->normal);
		new->side = ft_atof(s[7]) / 2;
		new->color = new_color(ft_atoi(s[8]), ft_atoi(s[9]), ft_atoi(s[10]));
		(col_range(new->color) || new->side < 0) ? g_rt.err = 3 : 0;
		new->check = (s[11] != NULL) ? 1 : 0;
		shell->shape = (void *)new;
		shell->id = sq;
		g_rt.shapes = (void *)shell;
	}
	while (s && s[++j] != NULL)
		free(s[j]);
	if (g_rt.err != 0 || j > 12)
		ft_puterr2('q');
	return (0);
}

int		ft_cy(char **s, int i, int j)
{
	t_cyl		*new;
	t_shapes	*shell;

	if (i == 12 || (g_rt.err = -1) != -1)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))) ||
		!(new = (t_cyl *)malloc(sizeof(t_cyl))))
			return (-1);
		shell->next = g_rt.shapes;
		new->pos = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->dir =
		normalized(vector_xyz(ft_atof(s[4]), ft_atof(s[5]), ft_atof(s[6])));
		new->r = ft_atof(s[7]) / 2.0;
		new->h = ft_atof(s[8]) / 2.0;
		new->color = new_color(ft_atoi(s[9]), ft_atoi(s[10]), ft_atoi(s[11]));
		(col_range(new->color) || new->r < 0 || new->h < 0) ? g_rt.err = 3 : 0;
		new->check = (s[12] != NULL) ? 1 : 0;
		shell->shape = (void *)new;
		g_rt.shapes = (void *)shell;
	}
	while (s && s[++j] != NULL)
		free(s[j]);
	if (g_rt.err != 0 || j > 13 || (shell->id = cy) != cy)
		ft_puterr2('c');
	return (0);
}

int		ft_tr(char **s, int i, int j)
{
	t_triangle	*new;
	t_shapes	*shell;

	if (i == 13 || (g_rt.err = -1) != -1)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))) ||
		!(new = (t_triangle *)malloc(sizeof(t_triangle))))
			return (-1);
		shell->next = g_rt.shapes;
		new->c1 = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->c2 = vector_xyz(ft_atof(s[4]), ft_atof(s[5]), ft_atof(s[6]));
		new->c3 = vector_xyz(ft_atof(s[7]), ft_atof(s[8]), ft_atof(s[9]));
		new->color = new_color(ft_atoi(s[10]), ft_atoi(s[11]), ft_atoi(s[12]));
		(col_range(new->color)) ? g_rt.err = 3 : 0;
		new->e1 = op_min(new->c2, new->c1);
		new->e2 = op_min(new->c3, new->c1);
		new->check = (s[13] != NULL) ? 1 : 0;
		shell->shape = (void *)new;
		g_rt.shapes = (void *)shell;
	}
	while (s && s[++j] != NULL)
		free(s[j]);
	if (g_rt.err != 0 || j > 14 || (shell->id = tr) != tr)
		ft_puterr2('t');
	return (0);
}
