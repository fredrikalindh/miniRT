/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initrt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 14:04:55 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/06 14:38:14 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	check_rt(char *f)
{
	int			i;

	i = -1;
	while (f && f[++i])
	{
		if (f[i] == '.' && f[i + 1] == 'r' && f[i + 2] == 't' && f[i + 3] == '\0')
		{
			g_rt.name[i] = '.';
			g_rt.name[++i] = 'b';
			g_rt.name[++i] = 'm';
			g_rt.name[++i] = 'p';
			g_rt.name[++i] = '\0';
			return (0);
		}
		g_rt.name[i] = f[i];
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
	list[9] = "filter";
}

static int	init_info(int fd, int argc)
{
	char		*line;
	char		**split;
	int			i;
	char		*list[LIST_SIZE];
	int 		(*fill_scene[LIST_SIZE])(char**);

	g_rt.save = (argc == 3) ? 1 : 0;
	init_list(list);
	init_ftptr(fill_scene);
	while ((get_next_line(fd, &line)) == 1 && g_rt.line++ >= 0)
	{
		split = ft_split(line);
		i = 0;
		if (split && split[0] != NULL && *split[0] != '\0')
		{
			while (i < LIST_SIZE && ft_strcmp(split[0], list[i]) != 0)
				i++;
			if (i == 9 && ++i == 10)
				g_rt.filter = 1;
			(i < LIST_SIZE) ? fill_scene[i](split) : 0 ;
		}
	}
	free(split);
	return (1);
}

int			init_scene(int argc, char *argv[])
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
		init_info(fd, argc);
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
		return (0);
	}
	exit(-1);
}
