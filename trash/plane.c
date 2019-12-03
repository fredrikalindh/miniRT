/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:58:45 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/15 12:32:01 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool p_intersect(t_intersection *intersection, t_plane plane)
{
	float dDotN;
	float t;

	dDotN = dot(intersection->ray.direction, plane.normal);
	if (dDotN == 0)
		return (false);
	t = dot(plane.position - intersection, ray.origin.normal) / dDotN; // nahh
	if (t <= RAY_T_MIN || t >= RAY_T_MAX)
		return (false);
	intersection->t = t;
	intersection->shape = &plane;
	return (true);
}
