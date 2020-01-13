/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initrt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:04:55 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/13 16:49:43 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	check_rt(char *f)
{
	int			i;
	int			j;

	i = -1;
	j = 0;
	while (f && f[++i])
	{
		if (f[i] == '.' && f[i + 1] == 'r' && f[i + 2] == 't' && !f[i + 3])
		{
			g_rt.name[j] = '.';
			g_rt.name[++j] = 'b';
			g_rt.name[++j] = 'm';
			g_rt.name[++j] = 'p';
			g_rt.name[++j] = '\0';
			return (0);
		}
		if (j < 36)
			g_rt.name[j++] = f[i];
	}
	return (1);
}

static void	init_list(char *list[LIST_SIZE])
{
	list[0] = "R";
	list[1] = "A";
	list[2] = "c";
	list[3] = "l";
	list[4] = "pl";
	list[5] = "sp";
	list[6] = "sq";
	list[7] = "tr";
	list[8] = "cy";
	list[9] = "dl";
}

static void	init_ftptr(int (*fill_scene[LIST_SIZE])(char**, int, int),
char *list[LIST_SIZE])
{
	init_list(list);
	g_rt.camera = NULL;
	g_rt.light = NULL;
	g_rt.d_light = NULL;
	g_rt.shapes = NULL;
	g_rt.a_light_r = -1;
	g_rt.res_x = 0;
	g_rt.line = 0;
	g_rt.filter = 0;
	fill_scene[0] = &ft_res;
	fill_scene[1] = &ft_amb;
	fill_scene[2] = &ft_cam;
	fill_scene[3] = &ft_lig;
	fill_scene[4] = &ft_pl;
	fill_scene[5] = &ft_sp;
	fill_scene[6] = &ft_sq;
	fill_scene[7] = &ft_tr;
	fill_scene[8] = &ft_cy;
	fill_scene[9] = &ft_lig;
}

static void	init_info(int fd, int i, int j)
{
	char		*line;
	char		**s;
	char		*list[LIST_SIZE];
	int			(*fill_scene[LIST_SIZE])(char**, int, int);

	init_ftptr(fill_scene, list);
	while ((get_next_line(fd, &line)) == 1 && g_rt.line++ >= 0)
	{
		s = ft_split(line);
		if ((i = 0) == 0 && s && s[0] != NULL && *s[0] != '\0')
		{
			while (i < LIST_SIZE && ft_strcmp(s[0], list[i]) != 0)
				i++;
			if ((j = 0) == 0 && s[0][0] != '#')
			{
				while (s && s[++j] != NULL && ft_strcmp(s[j], "check") != 0)
					is_digit(s[j]) == 0 ? g_rt.err = 1 : 0;
				(i < LIST_SIZE) ? fill_scene[i](s, j, -1) : ft_puterr3(s);
			}
			if ((j = -1) == -1 && s[0][0] == '#')
				while (s[++j] != NULL)
					free(s[j]);
		}
		free(s);
	}
}

void		init_scene(int argc, char *argv[])
{
	int			fd;
	t_camera	*p;

	if (argc < 2 || check_rt(argv[1]))
		ft_puterr("scene description file is missing");
	else if (argc > 2 && ft_strcmp(argv[2], "--save") != 0)
		ft_puterr("unvalid arguments");
	else if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_puterr("failed to open file");
	else
	{
		g_rt.save = (argc == 3) ? 1 : 0;
		init_info(fd, 0, 0);
		if (g_rt.res_x <= 0 || g_rt.res_y <= 0)
			ft_puterr("resolution missing");
		if (g_rt.camera == NULL)
			ft_puterr("need an eye to see!");
		if (close(fd) == -1)
			ft_puterr("failed to close file");
		p = g_rt.camera;
		while (p && p->next != NULL)
			p = p->next;
		p->next = g_rt.camera;
	}
}
