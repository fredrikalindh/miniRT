/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:58:45 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/15 12:46:01 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool	s_intersect(t_intersection *intersection, t_sphere sphere)
{
	t_ray ray;
	float a;
	float b;
	float c;
	float t;

	ray = intersection->ray;
	ray -= sphere.centre; // might have to use math ft
	a = length2(ray.direction);
	b = 2 * dot(ray.direction, ray.origin);
	c = length2(ray.origin) - sqr(sphere.radius);
	if ((sqr(b) - 4 * a * c) < 0.0)
		return (false);
	t = (-b - sqrt(sqr(b) - 4 * a * c)) / (2 * a);
	if (!(t > RAY_T_MIN && t < RAY_T_MAX))
		t = (-b + sqrt(sqr(b) - 4 * a * c)) / (2 * a));
	if (t > RAY_T_MIN && t < RAY_T_MAX)
		intersection->t = t;
	else
		return (false);
	intersection->shape = &sphere;
	return (true);
}
