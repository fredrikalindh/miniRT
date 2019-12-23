/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:28:23 by fredrika          #+#    #+#             */
/*   Updated: 2019/12/23 16:44:04 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

int		init_info(int fd, int argc)
{
	char	*line;
	char	**split; //split with whitespace and ','
	int		i;
	char	*list[LIST_SIZE];
	int 	(*fill_scene[LIST_SIZE])(char**);

	g_rt.save = (argc == 3) ? 1 : 0;
	init_list(list);
	init_ftptr(fill_scene);
	while ((get_next_line(fd, &line)) == 1 && g_rt.line++ >= 0)
	{
		split = ft_split(line); // splits line & frees str
		i = 0;
		if (split && split[0] != NULL && *split[0] != '\0')
		{
			while (i < LIST_SIZE && ft_strcmp(split[0], list[i]) != 0)
				i++;
			(i < LIST_SIZE) ? fill_scene[i](split) : 0 ; // has to free elements of split in it
		}
	}
	free(split);
	return (1);
}

int		init_scene(int argc, char *argv[])
{
	int		fd;
	t_camera *p;

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

int		exit_program(void *param)
{
	t_param *p;
	free_globals();
	p = (t_param *)param;
	write(1, "\033[1;30mClosing window...\n\033[0m", 29);
	mlx_destroy_window(p->mlx_ptr, p->win_ptr);
	exit(0);
}

int deal_key(int key, void *param)
{
	t_param *p;

	p = (t_param *)param;
	if (key == ESC || key == 256 || key == 259) // exit when esc key or ctrl+c
		exit_program(param);
	if (key == 8)
	{
		g_rt.camera = g_rt.camera->next;
		g_rt.image = g_rt.or_image;
		ray_trace();
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	}
	if ((key <= 126 && key >= 123) || key == 13 || (key >= 0 && key <= 2))
	{
		move(&g_rt.camera->position, &g_rt.camera->dir, key);
		g_rt.image = g_rt.or_image;
		ray_trace();
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	}
	// printf("%d\n", key);
	return (0);
}

void	create_header()
{
	int size;
	int div;
	int i;

	i = 1;
	div = 1000000000;
	size = g_rt.res_x * g_rt.res_y * 4;
	*g_rt.image++ = 'B';
	*g_rt.image++ = 'A';
	while (size / div == 0)
		div /= 10;
	while (div > 0)
	{
		*g_rt.image++ = size / div + '0';
		size = size % div;
		div /= 10;
		i++;
	}
	while (g_rt.image && ++i < 20)
	{
		g_rt.image += 6;
		*g_rt.image++ = '2';
		*g_rt.image++ = '0';
	}
}

void		open_image(char *print)
{
	create_header();
	if ((g_rt.fd = open("./minirt.bmp", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU)) == -1)
		ft_puterr("failed to create image.bmp");
	write(g_rt.fd, print, (g_rt.res_x * g_rt.res_y * 4) + 20);
}

int main(int ac, char *av[])
{
	t_param p;
	char *print;

	init_scene(ac, av);
	if (!(p.mlx_ptr = mlx_init()))
		return (-1);
	if (g_rt.save == 1)
	{
		if (!(g_rt.or_image = (char *)malloc((sizeof(char) * g_rt.res_x * g_rt.res_y * 4) + 21)))
			return (-1);
		print = g_rt.image;
		ray_trace();
		open_image(print);
		// printf("%d\n", g_rt.i);
		return (0);
	}
	p.bpp = 32;
	p.size_line = g_rt.res_x * 32;
	p.endian = 1;
	p.img_ptr = mlx_new_image(p.mlx_ptr, g_rt.res_x, g_rt.res_y);
	g_rt.or_image = mlx_get_data_addr(p.img_ptr, &p.bpp, &p.size_line, &p.endian); // BITS PER PIZEL & SIZE_LINE & ENDIAN
	write(1, "\033[1;36mRendering image...\n\033[0m", 30);
	g_rt.image = g_rt.or_image;
	ray_trace();
	write(1, "\033[1;36mDone!\n\033[0m", 17);
	p.win_ptr= mlx_new_window(p.mlx_ptr, g_rt.res_x, g_rt.res_y, "miniRT");
	mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img_ptr, 0, 0);
	mlx_key_hook(p.win_ptr, deal_key, (void *)&p);
	mlx_hook(p.win_ptr, X_BUTT, 0, exit_program, (void *)&p); // exit when X button
	mlx_loop(p.mlx_ptr);
}
