/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:06:12 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/22 19:44:51 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		ft_pl(char **s)
{
	int i;
	t_plane *new;
	t_shapes *shell;

	i = 0;
	while (s && s[++i] != NULL)
		is_digit(s[i]) == 0 ? g_rt.err = 1 : 0;
	if (i >= 10)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))))
			return (-1);
		if (!(new = (t_plane *)malloc(sizeof(t_plane))))
			return (-1);
		shell->next = g_rt.shapes;
		new->position = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->normal = vector_xyz(ft_atof(s[4]), ft_atof(s[5]), ft_atof(s[6]));
		outside_range2(new->normal) ? g_rt.err = 5 : normalize(&new->normal);
		new->color = new_color(ft_atoi(s[7]), ft_atoi(s[8]), ft_atoi(s[9]));
		if (outside_range(new->color))
			g_rt.err = 3;
		shell->shape = (void *)new;
		shell->id = pl;
		g_rt.shapes = (void *)shell;
	}
	i = -1;
	while (s && s[++i] != NULL)
		free(s[i]);
	if (i < 10 || g_rt.err != 0) 		// free shit == s and cam, light and shapes
		ft_puterr2('p');
	return (0);
}

int		ft_sp(char **s)
{
	int i;
	t_sphere *new;
	t_shapes *shell;

	i = 0;
	while (s && s[++i] != NULL)
		is_digit(s[i]) == 0 ? g_rt.err = 1 : 0;
	if (i >= 8)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))))
			return (-1);
		if (!(new = (t_sphere *)malloc(sizeof(t_sphere))))
			return (-1);
		shell->next = g_rt.shapes;
		new->center = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->radius = ft_atof(s[4]) / 2;
		new->color = new_color(ft_atoi(s[5]), ft_atoi(s[6]), ft_atoi(s[7]));
		if (outside_range(new->color))
			g_rt.err = 3;
		shell->shape = (void *)new;
		shell->id = sp;
		g_rt.shapes = (void *)shell;
	}
	i = -1;
	while (s && s[++i] != NULL)
		free(s[i]);
	if (i < 8 || g_rt.err != 0) 		// free shit == s and cam, light and shapes
		ft_puterr2('h');
	return (0);
}

int		ft_sq(char **s)
{
	int i;
	t_square *new;
	t_shapes *shell;

	i = 0;
	while (s && s[i] != NULL)
		i++;
	if (i >= 11)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))))
			return (-1);
		if (!(new = (t_square *)malloc(sizeof(t_square))))
			return (-1);
		shell->next = g_rt.shapes;
		new->center = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->normal = vector_xyz(ft_atof(s[4]), ft_atof(s[5]), ft_atof(s[6]));
		outside_range2(new->normal) ? g_rt.err = 5 : normalize(&new->normal);
		new->side = ft_atof(s[7]) / 2;
		new->color = new_color(ft_atoi(s[8]), ft_atoi(s[9]), ft_atoi(s[10]));
		shell->shape = (void *)new;
		shell->id = sq;
		g_rt.shapes = (void *)shell;
	}
	i = -1;
	while (s && s[++i] != NULL)
		free(s[i]);
	if (i < 11) 		// free shit == s and cam, light and shapes
		ft_puterr("error: incorrect square instruction");
	return (0);
}

int		ft_cy(char **s)
{
	int i;
	t_cyl *new;
	t_shapes *shell;

	i = 0;
	while (s && s[++i] != NULL)
		is_digit(s[i]) == 0 ? g_rt.err = 1 : 0;
	if (i >= 12)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))))
			return (-1);
		if (!(new = (t_cyl *)malloc(sizeof(t_cyl))))
			return (-1);
		shell->next = g_rt.shapes;
		new->position = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->direction = normalized(vector_xyz(ft_atof(s[4]), ft_atof(s[5]), ft_atof(s[6])));
		new->r = ft_atof(s[7]) / 2.0;
		new->h = ft_atof(s[8]) / 2.0;
		new->color = new_color(ft_atoi(s[9]), ft_atoi(s[10]), ft_atoi(s[11]));
		if (outside_range(new->color))
			g_rt.err = 3;
		shell->shape = (void *)new;
		shell->id = cy;
		g_rt.shapes = (void *)shell;
	}
	i = -1;
	while (s && s[++i] != NULL)
		free(s[i]);
	if (i < 12 || g_rt.err != 0) 	// free shit == s and cam, light and shapes
		ft_puterr2('c');
	return (0);
}

int		ft_tr(char **s)
{
	int i;
	t_triangle *new;
	t_shapes *shell;

	i = 0;
	while (s && s[++i] != NULL)
		is_digit(s[i]) == 0 ? g_rt.err = 1 : 0;
	if (i >= 13)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))))
			return (-1);
		if (!(new = (t_triangle *)malloc(sizeof(t_triangle))))
			return (-1);
		shell->next = g_rt.shapes;
		new->c1 = vector_xyz(ft_atof(s[1]), ft_atof(s[2]), ft_atof(s[3]));
		new->c2 = vector_xyz(ft_atof(s[4]), ft_atof(s[5]), ft_atof(s[6]));
		new->c3 = vector_xyz(ft_atof(s[7]), ft_atof(s[8]), ft_atof(s[9]));
		new->color = new_color(ft_atoi(s[10]), ft_atoi(s[11]), ft_atoi(s[12]));
		if (outside_range(new->color))
			g_rt.err = 3;
		new->e1 = op_min(new->c2, new->c1);
		new->e2 = op_min(new->c3, new->c1);
		shell->shape = (void *)new;
		shell->id = tr;
		g_rt.shapes = (void *)shell;
	}
	i = -1;
	while (s && s[++i] != NULL)
		free(s[i]);
	if (i < 13 || g_rt.err != 0) 		// free shit == s and cam, light and shapes
		ft_puterr2('t');
	return (0);
}
