/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:53:59 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/28 13:15:13 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "./minilibx/mlx.h"
# include <stdio.h>

# include "parce.h"


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define RAY_T_MIN 0.0001
# define RAY_T_MAX 1.0e30 // ?

typedef unsigned int	t_bool;

typedef	struct		s_param
{
	void	*mlx_ptr;
	void	*win_ptr;
}					t_param;

typedef struct		s_vector
{
	float	x;
	float	y;
	float	z;
}					t_vector;

typedef t_vector	t_point; // ??
//
// typedef struct		s_ray
// {
// 	t_point		origin; // ???
// 	t_vector	direction;
// 	float		tMax;
// }					t_ray;
//
// typedef struct		s_intersection
// {
// 	t_ray ray;
// 	float t;
// 	t_shape *shape;
// 	t_color color;
// }					t_intersection;
//
typedef struct		s_shapes // ??
{
	void	*shape;
	void	*next;
}					t_shapes;
//
typedef struct		s_sphere
{
	t_point		centre;
	float		radius;
	int			color;
}					t_sphere;

typedef struct		s_plane
{
	t_point		position;
	t_vector	normal;
	int			color;
}					t_plane;

typedef struct		s_cyl
{
	t_point		position;
	t_vector	direction;
	float		d;
	float		h;
	int			color;
}					t_cyl;

typedef struct		s_triangle
{
	t_point		c1;
	t_point		c2;
	t_point		c3;
	int			color;
}					t_triangle;

// typedef struct		s_camera
// {
// 	t_point origin;
// 	t_vector forward;
// 	t_vector up;
// 	t_vector height;
// 	float h;
// 	float w;
// }					t_camera;

typedef struct		s_camera
{
	t_vector		position;
	t_vector		vector;
	struct s_camera	*next;
}					t_camera;

typedef struct		s_light
{
	t_vector		coor;
	float			bright;
	int				color;
	struct s_light	*next;
}					t_light;
//
// typedef struct		s_image
// {
// 	int width;
// 	int height;
// 	float *data;
// }					t_image;

typedef struct		s_color // necessary ? could just use one int or floats ???
{
	int red:8;
	int green:8;
	int blue:8;
}					t_color;

typedef struct		s_rt
{
	int			save:1;

	int			res_x;
	int			res_y;
	float		a_light_r;
	int			a_light_c;
	t_camera	*camera;
	t_light		*light;
	t_shapes	*shapes;

	// t_vector	sp_coor;
	// float		sp_diam;
	// t_color		sp_col;
	//
	// t_vector	pl_coor;
	// t_vector	pl_d;
	// t_color		pl_col;
	//
	// t_vector	sq_coor;
	// t_vector	sq_ori;
	// float		sq_size;
	// t_color		sq_col;
	//
	// t_vector	cy_coor;
	// t_vector	cy_ori;
	// float		cy_d;
	// float		cy_h;
	// t_color		cy_col;
	//
	// t_vector	tr_c1;
	// t_vector	tr_c2;
	// t_vector	tr_c3;
	// t_color		tr_col;
}					t_rt;

int			get_next_line(int fd, char **line);
double		ft_atof(char *str);
int			ft_atoi(char *str);
void		ft_puterr(char *str);
int			ft_strcmp(char *s1, char *s2);
char		**ft_split(char *str);
t_vector	vector_xyz(float x, float y, float z);


#endif
