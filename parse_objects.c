/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:06:12 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/04 16:30:13 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		ft_pl(char **split)
{
	int i;
	t_plane *new;
	t_shapes *shell;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 10)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))))
			return (-1);
		if (!(new = (t_plane *)malloc(sizeof(t_plane))))
			return (-1);
		shell->next = g_rt.shapes;
		new->position = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->normal = vector_xyz(ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6]));
		new->color = new_color(ft_atoi(split[7]), ft_atoi(split[8]), ft_atoi(split[9]));
		shell->shape = (void *)new;
		shell->id = pl;
		g_rt.shapes = (void *)shell;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 10) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect plane instruction");
	return (0);
}

int		ft_sp(char **split)
{
	int i;
	t_sphere *new;
	t_shapes *shell;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 8)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))))
			return (-1);
		if (!(new = (t_sphere *)malloc(sizeof(t_sphere))))
			return (-1);
		shell->next = g_rt.shapes;
		new->center = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->radius = ft_atof(split[4]) / 2;
		new->color = new_color(ft_atoi(split[5]), ft_atoi(split[6]), ft_atoi(split[7]));
		shell->shape = (void *)new;
		shell->id = sp;
		g_rt.shapes = (void *)shell;
		// printf("%f %f %f %f %d %d %d \n", new->center.x, new->center.y, new->center.z, new->radius, new->color.r, new->color.g, new->color.b);
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 8) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect sphere instruction");
	return (0);
}

int		ft_sq(char **split)
{
	int i;
	t_square *new;
	t_shapes *shell;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 11)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))))
			return (-1);
		if (!(new = (t_square *)malloc(sizeof(t_square))))
			return (-1);
		shell->next = g_rt.shapes;
		new->center = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->orient = vector_xyz(ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6]));
		new->side = ft_atof(split[7]);
		new->color = new_color(ft_atoi(split[8]), ft_atoi(split[9]), ft_atoi(split[10]));
		shell->shape = (void *)new;
		shell->id = sq;
		g_rt.shapes = (void *)shell;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 11) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect square instruction");
	return (0);
}

int		ft_cy(char **split)
{
	int i;
	t_cyl *new;
	t_shapes *shell;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 12)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))))
			return (-1);
		if (!(new = (t_cyl *)malloc(sizeof(t_cyl))))
			return (-1);
		shell->next = g_rt.shapes;
		new->position = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->direction = vector_xyz(ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6]));
		new->d = ft_atof(split[7]);
		new->h = ft_atof(split[8]);
		new->color = new_color(ft_atoi(split[9]), ft_atoi(split[10]), ft_atoi(split[11]));
		shell->shape = (void *)new;
		shell->id = cy;
		g_rt.shapes = (void *)shell;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 12) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect cylinder instruction");
	return (0);
}

int		ft_tr(char **split)
{
	int i;
	t_triangle *new;
	t_shapes *shell;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 13)
	{
		if (!(shell = (t_shapes *)malloc(sizeof(t_shapes))))
			return (-1);
		if (!(new = (t_triangle *)malloc(sizeof(t_triangle))))
			return (-1);
		shell->next = g_rt.shapes;
		new->c1 = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->c2 = vector_xyz(ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6]));
		new->c2 = vector_xyz(ft_atof(split[7]), ft_atof(split[8]), ft_atof(split[9]));
		new->color = new_color(ft_atoi(split[10]), ft_atoi(split[11]), ft_atoi(split[12]));
		shell->shape = (void *)new;
		shell->id = tr;
		g_rt.shapes = (void *)shell;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 13) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect cylinder instruction");
	return (0);
}
