/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:58:45 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/13 13:10:45 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	ray()
{
	t_ray t;

	t.origin = vector_f(0.0);
	t.direction = 0;
	t.tMax = RAY_T_MAX;
	return (t);
}

t_ray	cpy_ray(t_ray old)
{
	t_ray t;

	t.origin = old.origin;
	t.direction = old.direction;
	t.tMax = old.tMAX;
	return (t);
}

t_ray	set_ray(t_point origin, t_vector direction, float tMax)
{
	t_ray t;

	t.origin = origin.origin;
	t.direction =  direction.direction;
	t.tMax = tMAX;
	return (t);
}

t_point	point_calc(t_point p, float t)
{
	return (p.origin + p.direction * t);
}
