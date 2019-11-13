/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:53:59 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/13 13:42:50 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include "libmlx.a"
# include <fcntl.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
double	ft_atof(char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define RAY_T_MIN 0.0001
# define RAY_T_MAX 1.0e30 // ?

typedef struct		s_rt
{
	int		r1;
	int		r2;
	int		a;
	int		ar;
	int		ag;
	int		ab;
	int		ab;
}					t_rt;

typedef struct		s_vector
{
	float	x;
	float	y;
	float	z;
}					t_vector;

typedef t_vector	t_point; // ??

typedef struct		s_ray
{
	t_point		origin; // ???
	t_vector	direction;
	float		tMax;
}					t_ray;

typedef struct		s_intersection
{
	t_ray ray;
	float t;
	t_shape *shape;
	t_color color;
}					t_intersection;

typedef struct		s_shapeset // ??
{
	t_shape shape;
	t_shape *next;
}					t_shapeset;

typedef struct		s_sphere
{


}					t_sphere;

typedef struct		s_plane
{


}					t_plane;

typedef struct		s_camera
{
	t_point origin;
	t_vector forward;
	t_vector up;
	t_vector height;
	float h;
	float w;
}					t_camera;

typedef struct		s_image
{
	int width;
	int height;
	float *data;
}					t_image;

typedef struct		s_color // necessary ? could just use one int or floats ???
{
	int red;
	int green;
	int blue;
}					t_color;


#endif
