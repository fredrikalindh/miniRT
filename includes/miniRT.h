/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:53:59 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/19 13:41:34 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# include "../minilibx/mlx.h"
# include "ft.h"
# include "structs.h"

# define MAX_X 2560
# define MAX_Y 1395
# define T_MIN 0.0001
# define T_MAX 1.0e30
# define EPSILON 0.00001
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

int			exit_program(void *param);
void		ft_puterr(char *str);
void		ft_puterr2(char c);
void		ft_puterr3(char **split);
void		free_globals();
int			col_range(t_color c);
int			v_range(t_vector v);
int			f_range(double d);
t_vector	vector_xyz(double x, double y, double z);
double		sqr(double f);
double		dot(t_vector v1, t_vector v2);
t_vector	cross(t_vector v1, t_vector v2);
double		length2(t_vector v);
double		length(t_vector v);
double		normalize(t_vector *v);
t_vector	normalized(t_vector v);
t_vector	op_add(t_vector v, t_vector op);
void		op_addp(t_vector *v, t_vector op);
t_vector	op_min(t_vector v, t_vector op);
void		op_minv(t_vector *v, t_vector op);
t_vector	op_mult_f(t_vector v, double f);
int			ft_pl(char **split, int i, int j);
int			ft_sp(char **split, int i, int j);
int			ft_sq(char **split, int i, int j);
int			ft_cy(char **split, int i, int j);
int			ft_tr(char **split, int i, int j);
int			ft_res(char **split, int i, int j);
int			ft_amb(char **split, int i, int j);
int			ft_cam(char **split, int i, int j);
int			ft_lig(char **split, int i, int j);
int			ft_dlig(char **s, int i, int j);
int			ray_trace();
t_color		ray_cast(t_intersection hit);
t_ray		compute_ray(float pixx, float pixy);
void		put_pixel(t_color c, int xy);
int			hit_cy(t_intersection *i, t_ray ray, void *shape);
int			intersect(t_intersection *hit, t_ray ray, t_shapes *shape, int f);
t_color		light_color(t_color l1, t_color l2, double d, double len);
t_color		total_color(t_color l, t_color c);
t_color		new_color(int r, int g, int b);
t_color		same_color(int col);
void		rot(double *a, double *b);
int			move(t_vector *pos, t_vector *dir, int key);
int			trans(int key);
void		open_image(int w, int h, int i);
void		init_scene(int argc, char *argv[]);
int			deal_mouse(int b, int x, int y, void *p);
int			deal_key(int key, void *param);
t_color		checked(double u, double v, t_color c);
void		set_lights(void);

t_rt		g_rt;

#endif
