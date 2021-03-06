/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:51:58 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/20 19:06:24 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		free_globals(void *prev, t_camera *start)
{
	while (g_rt.camera != NULL && (prev = (void *)g_rt.camera) != NULL)
	{
		g_rt.camera = g_rt.camera->next;
		free(prev);
		if (g_rt.camera == start)
			break ;
	}
	while (g_rt.light != NULL && (prev = (void *)g_rt.light) != NULL)
	{
		g_rt.light = g_rt.light->next;
		free(prev);
	}
	while (g_rt.d_light != NULL && (prev = (void *)g_rt.d_light) != NULL)
	{
		g_rt.d_light = g_rt.d_light->next;
		free(prev);
	}
	while (g_rt.shapes != NULL)
	{
		prev = g_rt.shapes;
		free(g_rt.shapes->shape);
		g_rt.shapes = g_rt.shapes->next;
		free(prev);
	}
}

int			exit_program(void *param)
{
	t_param		*p;

	free_globals(NULL, g_rt.camera);
	p = (t_param *)param;
	write(1, "\033[1;30mClosing window...\n\033[0m", 29);
	mlx_destroy_window(p->mlx_ptr, p->win_ptr);
	exit(0);
}

static void	put_type(char id)
{
	if (id == 'R')
		write(2, "resolution", 11);
	else if (id == 'A')
		write(2, "ambient light", 13);
	else if (id == 'C')
		write(2, "camera", 7);
	else if (id == 'l')
		write(2, "light", 5);
	else if (id == 'L')
		write(2, "directional light", 17);
	else if (id == 'h')
		write(2, "sphere", 6);
	else if (id == 'c')
		write(2, "cylinder", 8);
	else if (id == 't')
		write(2, "triangle", 8);
	else if (id == 'q')
		write(2, "square", 6);
	else if (id == 'p')
		write(2, "plane", 5);
	else
		write(2, "unknown", 7);
}

void		ft_puterr3(char **split)
{
	int i;

	i = -1;
	while (split && split[++i])
		free(split[i]);
	free(split);
	write(2, "\033[1;31mError: ", 14);
	write(2, "unknown instructions, on line: ", 31);
	ft_putnbr_fd(g_rt.line, 2);
	write(2, "\n\033[0m", 5);
	free_globals(NULL, g_rt.camera);
	exit(-1);
}

void		ft_puterr2(char id, char **split)
{
	free(split);
	write(2, "\033[1;31mError: ", 14);
	if (g_rt.err == 0 || g_rt.err == -1)
		write(2, "wrong instructions for ", 23);
	else if (g_rt.err == 1)
		write(2, "instruction for ", 16);
	else if (g_rt.err == 2)
		write(2, "double ", 7);
	else
		write(2, "incorrect ", 10);
	put_type(id);
	if (g_rt.err == 3)
		write(2, ", values not within the correct range", 37);
	else if (g_rt.err == 1)
		write(2, " contains non-digits", 20);
	else if (g_rt.err == 5)
		write(2, ", vector not normalized", 23);
	else if (g_rt.err == 6)
		write(2, ", FOV not withing 0-180", 23);
	write(2, ", on line: ", 11);
	ft_putnbr_fd(g_rt.line, 2);
	write(2, "\n\033[0m", 5);
	free_globals(NULL, g_rt.camera);
	exit(-1);
}
