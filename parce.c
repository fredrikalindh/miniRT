/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:02:57 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/09 16:23:56 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		ft_res(char **split)
{
	int i;

	i = 0;
	while (split && split[i] != NULL)
		i++;
	if (i >= 3)
	{
		g_rt.res_x = ft_min(ft_atoi(split[1]), MAX_X);
		g_rt.res_y = ft_min(ft_atoi(split[2]), MAX_Y);
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
		g_rt.a_light_c = new_color(ft_atoi(split[2]), ft_atoi(split[3]), ft_atoi(split[4]));
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
		new->dir = normalized(vector_xyz(ft_atof(split[4]), ft_atof(split[5]), ft_atof(split[6])));
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
		new->color = new_color(ft_atoi(split[5]), ft_atoi(split[6]), ft_atoi(split[7]));
		g_rt.light = new;
	}
	i = -1;
	while (split && split[++i] != NULL)
		free(split[i]);
	if (i < 8) 		// free shit == split and cam, light and shapes
		ft_puterr("error: incorrect light instruction");
	return (0);
}

void	init_ftptr(int (*fill_scene[LIST_SIZE])(char**))
{
	g_rt.camera = NULL;
	g_rt.light = NULL;
	g_rt.shapes = NULL;

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
