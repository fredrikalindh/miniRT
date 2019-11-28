/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:28:23 by fredrika          #+#    #+#             */
/*   Updated: 2019/11/28 15:03:37 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// void	free_rt()
// {
// 	t_camera *iter;
// 	t_camera *next;
// 	t_light *iter2;
// 	t_light *next2;
//
// 	iter = g_rt.camera;
// 	while (iter != NULL)
// 	{
// 		next = iter->next;
// 		free(iter);
// 		iter = next;
// 	}
// 	iter2 = g_rt.light;
// 	while (iter2 != NULL)
// 	{
// 		next2 = iter2->next;
// 		free(iter2);
// 		iter2 = next2;
// 	}
// 	iter = g_rt.shapes;
// 	while (iter != NULL) // extra for freeing shapes ?
// 	{
// 		next = iter->next;
// 		free(iter);
// 		iter = next;
// 	}
// }

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
	while (split && split[i] != NULL)
		i++;
	if (i >= 3)
	{
		g_rt.res_x = ft_atoi(split[1]);
		g_rt.res_y = ft_atoi(split[2]);
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 3)
	{
		free(split);
		ft_puterr("error: incorrect resolution");
		exit(-1);
	}
	return (0);
}

int		ft_amb(char **split)
{
	int i;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 5)
	{
		g_rt.a_light_r = ft_atof(split[1]);
		g_rt.a_light_c = (ft_atoi(split[2]) * 65536 + ft_atoi(split[3]) * 256 + ft_atoi(split[4]));
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 4)
		ft_puterr("error: incorrect ambient light instruction");
	return (0);
}

int		ft_cam(char **split)
{
	int i;
	t_camera *new;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 7)
	{
		if (!(new = (t_camera *)malloc(sizeof(t_camera))))
			return (-1);
		new->next = g_rt.camera;
		new->position = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->vector = vector_xyz(ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6]));
		g_rt.camera = new;
	}
	// printf("%f %f %f %f %f %f \n", g_rt.cam_pos.x, g_rt.cam_pos.y, g_rt.cam_pos.z, g_rt.cam_vec.x, g_rt.cam_vec.y, g_rt.cam_vec.z);
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 7)
		ft_puterr("error: incorrect camera instruction");
	return (0);
}

int		ft_lig(char **split)
{
	int i;
	t_light *new;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 8)
	{
		if (!(new = (t_light *)malloc(sizeof(t_light))))
			return (-1);
		new->next = g_rt.light;
		new->coor = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->bright = ft_atof(split[4]);
		new->color = (ft_atoi(split[5]) * 65536 + ft_atoi(split[6]) * 256 + ft_atoi(split[7]));
		g_rt.light = new;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 8) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect light instruction");
	return (0);
}

int		ft_pl(char **split) // best way?
{
	int i;
	t_plane *new;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 10)
	{
		if (!(new = (t_plane *)malloc(sizeof(t_plane))))
			return (-1);
		new->next = g_rt.shapes->planes;
		new->position = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->normal = vector_xyz(ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6]));
		new->color = (ft_atoi(split[7]) * 65536 + ft_atoi(split[8]) * 256 + ft_atoi(split[9]));
		g_rt.shapes->planes = new;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 10) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect plane instruction");
	return (0);
}

int		ft_sp(char **split) // best way?
{
	int i;
	t_sphere *new;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 8)
	{
		if (!(new = (t_sphere *)malloc(sizeof(t_sphere))))
			return (-1);
		new->next = g_rt.shapes->spheres;
		new->center = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->radius = ft_atof(split[4]) / 2;
		new->color = (ft_atoi(split[5]) * 65536 + ft_atoi(split[6]) * 256 + ft_atoi(split[7]));
		g_rt.shapes->spheres = new;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 8) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect sphere instruction");
	return (0);
}

int		ft_sq(char **split) // best way?
{
	int i;
	t_square *new;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 11)
	{
		if (!(new = (t_square *)malloc(sizeof(t_square))))
			return (-1);
		new->next = g_rt.shapes->squares;
		new->center = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->orient = vector_xyz(ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6]));
		new->side = ft_atof(split[7]);
		new->color = (ft_atoi(split[8]) * 65536 + ft_atoi(split[9]) * 256 + ft_atoi(split[10]));
		g_rt.shapes->squares = new;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 11) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect square instruction");
	return (0);
}

int		ft_cy(char **split) // best way?
{
	int i;
	t_cyl *new;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 12)
	{
		if (!(new = (t_cyl *)malloc(sizeof(t_cyl))))
			return (-1);
		new->next = g_rt.shapes->cyls;
		new->position = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->direction = vector_xyz(ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6]));
		new->d = ft_atof(split[7]);
		new->h = ft_atof(split[8]);
		new->color = (ft_atoi(split[9]) * 65536 + ft_atoi(split[10]) * 256 + ft_atoi(split[11]));
		g_rt.shapes->cyls = new;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 12) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect cylinder instruction");
	return (0);
}

int		ft_tr(char **split) // best way?
{
	int i;
	t_triangle *new;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 13)
	{
		if (!(new = (t_triangle *)malloc(sizeof(t_triangle))))
			return (-1);
		new->next = g_rt.shapes->triangles;
		new->c1 = vector_xyz(ft_atof(split[1]), ft_atof(split[2]), ft_atof(split[3]));
		new->c2 = vector_xyz(ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6]));
		new->c2 = vector_xyz(ft_atof(split[7]), ft_atof(split[8]), ft_atof(split[9]));
		new->color = (ft_atoi(split[10]) * 65536 + ft_atoi(split[11]) * 256 + ft_atoi(split[12]));
		g_rt.shapes->triangles = new;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 13) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect cylinder instruction");
	return (0);
}

void	init_ftptr(int (*fill_scene[LIST_SIZE])(char**))
{
	if (!(g_rt.camera = (t_camera *)malloc(sizeof(t_camera))))
		exit (-1);
	g_rt.camera->next = NULL;
	if (!(g_rt.light = (t_light *)malloc(sizeof(t_light))))
		exit (-1);
	g_rt.light->next = NULL;
	if (!(g_rt.shapes = (t_shapes *)malloc(sizeof(t_shapes))))
		exit (-1);
	g_rt.shapes->planes = NULL;
	g_rt.shapes->spheres = NULL;
	g_rt.shapes->squares = NULL;
	g_rt.shapes->triangles = NULL;
	g_rt.shapes->cyls = NULL;

	fill_scene[0] = &ft_res;
	fill_scene[1] = &ft_amb;
	fill_scene[2] = &ft_cam;
	fill_scene[3] = &ft_lig;
	fill_scene[4] = &ft_pl;
	fill_scene[5] = &ft_sp;
	fill_scene[6] = &ft_sq;
	fill_scene[7] = &ft_tr;
	fill_scene[8] = &ft_cy;
}

// int		init_info(int fd, int argc)
// {
// 	char	*line;
// 	char	**split; //split with whitespace and ','
// 	int 	(*fill_scene[LIST_SIZE])(char**);
// 	enum scene_info{R, A, c, l, pl, sp, sq, tr, cy}test;
//
// 	if (argc == 3)
// 		g_rt.save = 1;
// 	init_ftptr(fill_scene);
// 	while ((get_next_line(fd, &line)) == 1)
// 	{
// 		split = ft_split(line); // splits line & frees str
// 		if ((test = split[0]) >= 0)
// 		{
// 			// printf("[%s] [%s] [%s] [%s]\n", split[0], split[1], split[2], split[3]);
// 			fill_scene[test](split); // has to free elements of split in it
// 		}
// 	}
// 	free(line);
// 	return (1);
// }

int		init_info(int fd, int argc)
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
	while ((get_next_line(fd, &line)) == 1)
	{
		split = ft_split(line); // splits line & frees str
		i = 0;
		if (split && split[0] != NULL && *split[0] != '\0')
		{
			// printf("[%s] [%s] [%s] [%s]\n", split[0], split[1], split[2], split[3]);
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

	if (argc < 2 || check_rt(argv[1]))
		ft_puterr("error: scene description file is missing");
	else if (argc > 2 && ft_strcmp(argv[2], "--save") != 0)
		ft_puterr("error: unvalid arguments");
	else if ((fd = open(argv[1], O_RDONLY)) == -1)
		ft_puterr("error opening file");
	else
	{
		init_info(fd, argc);
		close(fd);
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
	int x;
	int y;

	init_scene(ac, av);
	if (!(g_p.mlx_ptr = mlx_init()))
		return (-1);
	g_p.win_ptr= mlx_new_window(g_p.mlx_ptr, g_rt.res_x, g_rt.res_y, "miniRT");
	for (x = 0; x < 100; x++)
		for (y = 0; y < 100; y++)
			mlx_pixel_put(g_p.mlx_ptr, g_p.win_ptr, x, y, g_rt.a_light_c);
		for (x = 100; x <= 500; x++)
			for (y = 100; y <= 500; y++)
			mlx_pixel_put(g_p.mlx_ptr, g_p.win_ptr, x, y, g_rt.light->color);
	// c = (16711680 * 1/*r*/ + 65280 * 1/*g*/ + 255 * 1/*b*/);
	mlx_key_hook(g_p.win_ptr, deal_key, (void *)0);
	mlx_hook(g_p.win_ptr, 17, 0, exit_program, (void *)0); // exit when X button
	mlx_loop(g_p.mlx_ptr);
}
