/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:51:58 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/23 16:11:17 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_globals()
{
	void *prev;
	t_camera *start;

	start = g_rt.camera;
	while(g_rt.camera != NULL && g_rt.camera->next != start)
	{
		prev = (void *)g_rt.camera;
		g_rt.camera = g_rt.camera->next;
		free(prev);
	}
	while (g_rt.light != NULL)
	{
		prev = (void *)g_rt.light;
		g_rt.light = g_rt.light->next;
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

void	ft_puterr2(char id)
{
	write(2, "\033[1;31m", 7);
	write(2, "Error: ", 7);
	if (g_rt.err == 0)
		write(2, "missing arguments for ", 22);
	else if (g_rt.err == 2)
		write(2, "double ", 7);
	else
		write(2, "incorrect ", 10);
	if (id == 'R')
		write(2, "resolution", 11);
	else if (id == 'A')
		write(2, "ambient light", 13);
	else if (id == 'c')
		write(2, "camera", 7);
	else if (id == 'l')
		write(2, "light", 5);
	else if (id == 'h')
		write(2, "sphere", 6);
	else if (id == 'c')
		write(2, "cylinder", 8);
	else if (id == 't')
		write(2, "triangle", 8);
	else if (id == 'q')
		write(2, "square", 6);
	else
		write(2, "unknown", 7);
	if (g_rt.err == 3)
		write(2, " color not within the correct range", 35);
	else if (g_rt.err == 5)
		write(2, " vector not normalized", 22);
	write(2, " on line: ", 10);
	ft_putnbr_fd(g_rt.line, 2);
	write(2, "\n\033[0m", 5);
	free_globals();
	exit (-1);
}
