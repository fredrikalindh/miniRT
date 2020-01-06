/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:53:59 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/06 16:39:23 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# include "../minilibx/mlx.h"
# include "ft.h"

# include <stdio.h> // OBS

# define MAX_X 2560
# define MAX_Y 1395

# define LIST_SIZE 10

# define ESC 53
# define C 8
# define L 37
# define X_BUTT 17
# define Q 12
# define W 13
# define E 14
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123
# define DOT 43
# define CMA 47
# define PLUS 24
# define MIN 27
# define H 4
# define B 11
# define TAB 48

# define T_MIN 0.0001
# define T_MAX 1.0e30
# define EPSILON 0.00001

typedef	struct		s_param // insert inside g_rt?
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
}					t_param;

typedef struct		s_vector
{
	double	x;
	double	y;
	double	z;
}					t_vector;

typedef t_vector	t_point;

typedef struct		s_ray
{
	t_point		origin; // ???
	t_vector	dir;
}					t_ray;

typedef struct		s_color // -> double ??
{
	unsigned int r; // :16
	unsigned int g; // :16
	unsigned int b; // :16
}					t_color;

typedef struct		s_sphere
{
	t_color			color;
	t_point			center;
	double			radius;
}					t_sphere;

typedef struct		s_plane
{
	t_color			color;
	t_point			pos;
	t_vector		normal;
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
}					t_cyl;

typedef struct		s_triangle
{
	t_color				color;
	t_point				c1;
	t_point				c2;
	t_point				c3;
	t_point				e1;
	t_point				e2;
	t_point				e3;
	// t_point				normal;
}					t_triangle;

typedef struct		s_square
{
	t_color			color;
	t_point			center;
	t_vector		normal;
	double			side;
}					t_square;

typedef struct		s_shapes
{
	enum id{sp, pl, cy, tr, sq}	id;
	void					*shape;
	void					*next;
}					t_shapes;

typedef struct		s_camera
{
	t_point			pos;
	t_vector		dir;
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
	t_ray ray;
	double t;
	t_vector normal;
	t_point hit;
	void *shape;
	t_color color;
}					t_intersection;

typedef struct		s_trans
{
	t_point		*origin; // ???
	t_vector	*dir;
	t_vector	*c3;
	double		*r;
	double		*h;
	// t_shapes	*shape;
}					t_trans;

typedef struct s_image {
	unsigned char		*f;
	unsigned char		*i;
	unsigned char		*bmppad;
	char*				data;
}	t_image;

typedef struct		s_rt
{
	unsigned int	save:1;
	char			name[30];
	unsigned int	err:8;
	char			*image;
	char			*or_image;
	int				fd:4;
	int				filter:2;
	int				line;
	t_trans			to_change;
	int				res_x;
	int				res_y;
	double			a_light_r;
	t_color			a_light_c;
	t_camera		*camera;
	t_light			*light;
	t_shapes		*shapes;
}					t_rt;

int			exit_program(void *param);
void		ft_puterr(char *str);
void		ft_puterr2(char c);
void		free_globals();
int			outside_range(t_color c);
int			outside_range2(t_vector v);
// functions for vector calculations and creation
t_vector	vector_xyz(double x, double y, double z);
t_vector	vector_f(double f);
// vector_math
double		sqr(double f);
double		dot(t_vector v1, t_vector v2);
t_vector	cross(t_vector v1, t_vector v2);
t_vector	cross(t_vector v1, t_vector v2);
double		length2(t_vector v);
double		length(t_vector v);
double		normalize(t_vector *v);
t_vector	normalized(t_vector v);

// op_vectors
t_vector	op_add(t_vector v, t_vector op);
void		op_addp(t_vector *v, t_vector op);
t_vector	op_min(t_vector v, t_vector op);
void		op_minv(t_vector *v, t_vector op);
void		op_mult(t_vector *v, t_vector op);
t_vector	op_mult_f(t_vector v, double f);

void		clamp(t_color *c);
void		apply_gamma(t_color *c, double exposure, double gamma);
int			ret_color(t_color c);
t_color		new_color(int r, int g, int b);

// parce_objects.c
int			ft_pl(char **split);
int			ft_sp(char **split);
int			ft_sq(char **split);
int			ft_cy(char **split);
int			ft_tr(char **split);
// parce.c
int			ft_res(char **split);
int			ft_amb(char **split);
int			ft_cam(char **split);
int			ft_lig(char **split);
void		init_ftptr(int (*fill_scene[LIST_SIZE])(char**));
// rt.c
int			ray_trace();
t_color 	ray_cast(t_intersection hit);
t_ray		compute_ray(float pixx, float pixy);
int			hit_cy(t_intersection *i, t_ray ray, void *shape);
int 		intersect(t_intersection *hit, t_ray ray, t_shapes *shape, int f);

//color.c
t_color		same_color(int col);
void		apply_gamma(t_color *c, double exposure, double gamma);
void		clamp(t_color *c);
t_color		color_add(t_color c1, t_color c2);
t_color		color_mult(t_color c1, double f);


int 		move(t_vector *pos, t_vector *dir, int key);
int			trans(int key);

void		open_image(int w, int h, int i);
int			init_scene(int argc, char *argv[]);

t_rt	g_rt;

#endif
