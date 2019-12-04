/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:53:59 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/04 19:21:46 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# include "./minilibx/mlx.h"
# include "./libft/ft.h"

# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define LIST_SIZE 9
# define RESOLUTION	"R"
# define AMBIENT	"A"
# define CAMERA		"c"
# define LIGHT		"l"
# define PLANE		"pl"
# define SPHERE		"sp"
# define SQUARE		"sq"
# define TRIANGLE	"tr"
# define CYLINDER	"cy"

# define ESC 53
# define CTRL_C 8
# define X_BUTT 17
# define RAY_T_MIN 0.0001
# define RAY_T_MAX 1.0e30

typedef enum {FALSE, TRUE} t_bool;

typedef	struct		s_param
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
	t_vector	direction;
	//enum type{prim, shad, reflx, refract}id;
	//int		nr:4;
}					t_ray;

typedef struct		s_color // -> double ??
{
	unsigned int r:8;
	unsigned int g:8;
	unsigned int b:8;
}					t_color;

typedef struct		s_sphere
{
	t_point			center;
	double			radius;
	t_color			color;
}					t_sphere;

typedef struct		s_plane
{
	t_point			position;
	t_vector		normal;
	t_color			color;
}					t_plane;

typedef struct		s_cyl
{
	t_point			position;
	t_vector		direction;
	double			d;
	double			h;
	t_color			color;
}					t_cyl;

typedef struct		s_triangle
{
	t_point				c1;
	t_point				c2;
	t_point				c3;
	t_color				color;
}					t_triangle;

typedef struct		s_square
{
	t_point			center;
	t_vector		orient;
	double			side;
	t_color			color;
}					t_square;

// typedef struct		s_shapes // ??
// {
// 	t_plane		*planes;
// 	t_sphere	*spheres;
// 	t_square	*squares;
// 	t_triangle	*triangles;
// 	t_cyl		*cyls;
// }					t_shapes;

typedef struct		s_shapes // ?? could have one t per box so i.e. 100x100x100 = one box
{
	enum id{sp, pl, cy, tr, sq}	id;
	void					*shape;
	void					*next;
}					t_shapes;

// typedef struct		s_camera
// {
// 	t_point origin;
// 	t_vector forward;
// 	t_vector up;
// 	t_vector height;
// 	double h;
// 	double w;
// }					t_camera;

typedef struct		s_camera
{
	t_point			position;
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
	void *shape;
	t_color color;
}					t_intersection;

// typedef struct		s_image
// {
// 	int width;
// 	int height;
// 	double *data;
// }					t_image;

typedef struct		s_rt
{
	int			save:1;
	char		*image;
	int			fd:4;

	int			res_x:12;
	int			res_y:12;
	int			fov;
	double 		m[9];
	double		a_light_r;
	t_color		a_light_c;
	t_camera	*camera;
	t_light		*light;
	t_shapes	*shapes;
}					t_rt;

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
t_vector	op_min(t_vector v, t_vector op);
void		op_minv(t_vector *v, t_vector op);
void		op_mult(t_vector *v, t_vector op);
t_vector	op_mult_f(t_vector v, float f);

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
// t_vector	mult_vec_matrix(t_vector src);
// void		get_camtoworld();
void		init_iftptr(t_bool (*intersect[5])(t_intersection *, t_ray, void *));
// intersect.c
t_bool		sp_intersect(t_intersection *intersection, t_ray ray, void *shape);
t_bool		pl_intersect(t_intersection *intersection, t_ray ray, void *shape);
t_bool tr_intersect(t_intersection *intersection, t_ray inside, void *shape);

//color.c
t_color		same_color(int col);
void		apply_gamma(t_color *c, double exposure, double gamma);
void		clamp(t_color *c);
t_color		color_add(t_color c1, t_color c2);

t_rt	g_rt;

#endif
