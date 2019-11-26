/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:28:23 by fredrika          #+#    #+#             */
/*   Updated: 2019/11/26 18:28:44 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_param g_p;
t_rt	g_rt;

int		check_rt(char *f)
{
	int		i;

	i = -1;
	while (f && f[++i])
	{
		if (f[i] == '.' && f[i + 1] == 'r' && f[i + 2] == 't' && f[i + 3] == '\0')
			return (0);
	}
	return (1);
}

void	init_list(char *list[LIST_SIZE])
{
	list[0] = RESOLUTION;
	list[1] = AMBIENT;
	list[2] = CAMERA;
	list[3] = LIGHT;
	list[4] = PLANE;
	list[5] = SPHERE;
	list[6] = SQUARE;
	list[7] = TRIANGLE;
	list[8] = CYLINDER;
}

int		ft_res(char **split)
{
	int i;

	i = 0;
	g_rt.res_x = ft_atoi(split[1]);
	g_rt.res_y = ft_atoi(split[2]);
	while (split && split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	printf("%d\n", i);
	if (i != 3)
	{
		free(split);
		ft_puterr("error: incorrect resolution");
		exit(-1);
	}
	return (0);
}

void	init_ftptr(int (*fill_scene[LIST_SIZE])(char**))
{
	fill_scene[0] = &ft_res;
	// fill_scene[1] = ft_amb;
	// fill_scene[2] = ft_cam;
	// fill_scene[3] = ft_lig;
	// fill_scene[4] = ft_pl;
	// fill_scene[5] = ft_sp;
	// fill_scene[6] = ft_sq;
	// fill_scene[7] = ft_tr;
	// fill_scene[8] = ft_cy;
}

void	init_info(int fd, int argc, int ret)
{
	char	*line;
	char	**split; //split with whitespace and ','
	int		i;
	char	*list[LIST_SIZE];
	int 	(*fill_scene[LIST_SIZE])(char**);

	if (argc == 3)
		g_rt.save = 1;
	init_list(list);
	init_ftptr(fill_scene);
	while (ret == 1)
	{
		if ((ret = get_next_line(fd, &line)) == -1)
			return ;
		split = ft_split(line); // splits line & frees str
		printf("[%s] [%s] [%s] [%s]\n", split[0], split[1], split[2], split[3]);
		i = 0;
		printf("%s\n", list[i]);
		while (i < LIST_SIZE && ft_strcmp(split[0], list[i]) != 0)
			i++;
		printf("%d\n", i);
		i != LIST_SIZE ? fill_scene[i](split) : 0; // has to free elements of split in it
		free(split);
	}
}

int		init_scene(int argc, char *argv[])
{
	int		fd;

	if (argc < 2 || check_rt(argv[1]))
		ft_puterr("error: scene description file is missing");
	else if (argc > 2 && ft_strcmp(argv[2], "--save") != 0)
		ft_puterr("error: unvalid arguments");
	else if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_puterr("error opening file");
	else
	{
		init_info(fd, argc, 1);
		return (0);
	}
	exit(-1);
}

int		exit_program(void)
{
	// free stuff
	mlx_destroy_window(g_p.mlx_ptr, g_p.win_ptr);
	exit(0);
}

int deal_key(int key, void *param)
{
	(void)param;
	if (key == 53 || key == 8) // exit when esc key or ctrl+c
		exit_program();
	return (0);
}

int main(int ac, char *av[])
{
	init_scene(ac, av);
	printf("WE GET HERE?\n");
	if (!(g_p.mlx_ptr = mlx_init()))
		return (-1);
	g_p.win_ptr= mlx_new_window(g_p.mlx_ptr, 500, 500, "miniRT");
	// c = (16711680 * 1/*r*/ + 65280 * 1/*g*/ + 255 * 1/*b*/);
	mlx_key_hook(g_p.win_ptr, deal_key, (void *)0);
	mlx_hook(g_p.win_ptr, 17, 0, exit_program, (void *)0); // exit when X button
	mlx_loop(g_p.mlx_ptr);
}
