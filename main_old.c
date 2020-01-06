/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:28:23 by fredrika          #+#    #+#             */
/*   Updated: 2020/01/06 00:37:38 by frlindh          ###   ########.fr       */
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
			if (i == 9 && ++i == 10)
				g_rt.filter = 1;
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

void	set_object(int key)
{
	static t_shapes *s = NULL;

	g_rt.to_change.origin = NULL;
	g_rt.to_change.direction = NULL;
	g_rt.to_change.r = NULL;
	g_rt.to_change.h = NULL;
	if (s == NULL)
		s = g_rt.shapes;
	g_rt.to_change.origin = &((t_sphere *)s->shape)->center;
	if (s->id == 2 || s->id == 3 || s->id == 5)
		g_rt.to_change.direction = &((t_plane *)s->shape)->normal;
	if (s->id == 1)
		g_rt.to_change.r = &((t_sphere *)s->shape)->radius;
	if (s->id == 3 || s->id == 5)
		g_rt.to_change.r = &((t_cyl *)s->shape)->r;
	if (s->id == 3)
		g_rt.to_change.h = &((t_cyl *)s->shape)->h;
	if (key == O)
		s = s->next;
}

void	set_lights()
{
	static t_light *l = NULL;

	if (l == NULL)
		l = g_rt.light;
	g_rt.to_change.origin = &l->coor;
	g_rt.to_change.direction = NULL;
	g_rt.to_change.r = &l->bright;
	g_rt.to_change.h = NULL;
	l = l->next;
}

int		deal_mouse(int b, int x, int y, void *p)
{
	t_intersection hit;
	t_shapes *shape;
	int		i;
	int		id;
	(void)p;

	hit.ray = compute_ray((float)x / g_rt.res_x, (float)y / g_rt.res_y);
	shape = g_rt.shapes;
	hit.t = RAY_T_MAX;
	while (shape != NULL)
	{
		if ((i = intersect(&hit, hit.ray, shape, 0)) > 0)
			id = i;
		shape = shape->next;
	}
	if (hit.t != RAY_T_MAX && b == 1)
	{
		g_rt.to_change.origin = &((t_sphere *)hit.shape)->center;
		g_rt.to_change.direction = (id == 2 || id == 3 || id == 5) ? &((t_plane *)hit.shape)->normal : 0;
		g_rt.to_change.r = (id == 1) ? &((t_sphere *)hit.shape)->radius : 0;
		g_rt.to_change.c3 = (id == 4) ? &((t_triangle *)hit.shape)->c3 : 0;
		if (id == 3 || id == 5)
			g_rt.to_change.r = &((t_cyl *)hit.shape)->r;
		g_rt.to_change.h = (id == 3) ? &((t_cyl *)hit.shape)->h : 0;
	}
	return (0);
}

int deal_key(int key, void *param)
{
	t_param *p;
	int		flag;

	p = (t_param *)param;
	if (key == ESC) // exit when esc key c
		exit_program(param);
	if (key == TAB && (flag = 1) == 1)
		g_rt.camera = g_rt.camera->next;
	if ((key == C || key == TAB) && (g_rt.to_change.origin = &g_rt.camera->position) != NULL)
		g_rt.to_change.direction = &g_rt.camera->dir;
	else if (key == L)
		set_lights();
	else if (key == O)
		set_object(key);
	else if (key == PLUS || key == MIN || key == H || key == B)
		flag = trans(key);
	else if ((key <= UP && key >= LEFT) || (key >= Q && key <= E) || (key >= A && key <= D) || key == DOT || key == CMA)
		flag = move(g_rt.to_change.origin, g_rt.to_change.direction, key);
	if (flag == 1)
	{
		g_rt.image = g_rt.or_image;
		ray_trace();
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->img_ptr, 0, 0);
	}
	// printf("%d\n", key);
	return (0);
}

void	create_header(t_header *i)
{
	int filesize;

	filesize = g_rt.res_x * g_rt.res_y * 4 + 54;
	i->type = 0x4d42;
	i->size1 = (unsigned char)(filesize    );
	i->size2 = (unsigned char)(filesize>> 8);
	i->size3 = (unsigned char)(filesize>> 16);
	i->size4 = (unsigned char)(filesize>> 24);
	i->offset = 54;
	i->dib_header_size = 40;
	i->width_px = g_rt.res_x;
	i->height_px = g_rt.res_y;
	i->num_planes = 1;       // Number of color planes
	i->bits_per_pixel = 32;
	i->compression = 3;      // Compression type
	i->image_size = filesize - 54;
	i->x_resolution_ppm = 0; // Pixels per meter
	i->y_resolution_ppm = 0; // Pixels per meter
	i->num_colors = 0;       // Number of colors
	i->important_colors = 0; // Important colors
}

void		open_image()
{
	t_image img;

	if (!(g_rt.image = (char *)malloc(g_rt.res_x * g_rt.res_y * 4 + 1)))
		exit (-1);
	img.data = g_rt.image;
	ray_trace();
	create_header(&img.header);
	if ((g_rt.fd = open("./minirt.bmp", O_CREAT | O_WRONLY | O_TRUNC)) == -1)
		ft_puterr("failed to create image.bmp");
	write(g_rt.fd, &img.header, 54);
	*g_rt.image = '\0';
	write(g_rt.fd, img.data, img.header.image_size);
	if (close(g_rt.fd) == -1)
		ft_puterr("failed to close image");
}

int main(int ac, char *av[])
{
	t_param p;

	init_scene(ac, av);
	if (g_rt.save == 1)
	{
		open_image();
		return (0);
	}
	if (!(p.mlx_ptr = mlx_init()))
		return (-1);
	p.bpp = 32;
	p.size_line = g_rt.res_x * 32;
	p.endian = 1;
	p.img_ptr = mlx_new_image(p.mlx_ptr, g_rt.res_x, g_rt.res_y);
	g_rt.or_image = mlx_get_data_addr(p.img_ptr, &p.bpp, &p.size_line, &p.endian); // BITS PER PIZEL & SIZE_LINE & ENDIAN
	g_rt.image = g_rt.or_image;
	g_rt.to_change.origin = &g_rt.camera->position;
	g_rt.to_change.direction = &g_rt.camera->dir;
	write(1, "\033[1;36mRendering image...\n\033[0m", 30);
	ray_trace();
	p.win_ptr= mlx_new_window(p.mlx_ptr, g_rt.res_x, g_rt.res_y, "miniRT");
	mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img_ptr, 0, 0);
	mlx_key_hook(p.win_ptr, deal_key, (void *)&p);
	mlx_mouse_hook(p.win_ptr, deal_mouse, (void *)0);
	mlx_hook(p.win_ptr, X_BUTT, 0, exit_program, (void *)&p); // exit when X button
	mlx_loop(p.mlx_ptr);
}
