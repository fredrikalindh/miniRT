/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 13:40:08 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/19 13:41:11 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef	struct		s_param
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data;
	int				bpp;
	int				sl;
	int				endian;
}					t_param;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef t_vector	t_point;

typedef struct		s_ray
{
	t_point			origin;
	t_vector		dir;
}					t_ray;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_sphere
{
	t_color			color;
	t_point			center;
	double			radius;
	unsigned int	check:2;
}					t_sphere;

typedef struct		s_plane
{
	t_color			color;
	t_point			pos;
	t_vector		normal;
	unsigned int	check:2;
}					t_plane;

typedef struct		s_cyl
{
	t_color			color;
	t_point			pos;
	t_vector		dir;
	double			r;
	double			h;
	double			d;
	int				first:2;
	unsigned int	check:2;
}					t_cyl;

typedef struct		s_triangle
{
	t_color			color;
	t_point			c1;
	t_point			c2;
	t_point			c3;
	t_point			e1;
	t_point			e2;
	t_point			e3;
	unsigned int	check:2;
}					t_triangle;

typedef struct		s_square
{
	t_color			color;
	t_point			center;
	t_vector		normal;
	double			side;
	unsigned int	check:2;
}					t_square;

typedef struct		s_shapes
{
	enum	{sp, pl, cy, tr, sq}id;
	void						*shape;
	void						*next;
}					t_shapes;

typedef struct		s_camera
{
	t_point			pos;
	t_vector		dir;
	t_vector		right;
	int				fov;
	struct s_camera	*next;
}					t_camera;

typedef struct		s_light
{
	t_vector		coor;
	double			bright;
	t_color			color;
	struct s_light	*next;
}					t_light;

typedef struct		s_intersection
{
	t_ray			ray;
	double			t;
	t_vector		normal;
	t_point			hit;
	void			*shape;
	t_color			color;
}					t_intersection;

typedef struct		s_trans
{
	t_point			*origin;
	t_vector		*dir;
	t_vector		*c3;
	double			*r;
	double			*h;
}					t_trans;

typedef struct		s_image
{
	unsigned char	*f;
	unsigned char	*i;
	unsigned char	*bmppad;
	unsigned int	w;
	unsigned int	h;
	char			*data;
}					t_image;

typedef struct		s_rt
{
	unsigned int	save:1;
	char			name[40];
	int				err:8;
	char			*image;
	int				fd:4;
	unsigned int	filter:2;
	int				line;
	t_trans			select;
	int				res_x;
	int				res_y;
	double			a_light_r;
	t_color			a_light_c;
	t_camera		*camera;
	t_light			*light;
	t_light			*d_light;
	t_shapes		*shapes;
}					t_rt;

#endif
