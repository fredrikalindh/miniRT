/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:03:06 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/13 13:26:57 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_camera	camera(t_point origin, t_vector target, t_vector upguide, float fov, float aRatio) // too many arguments
{
	t_camera cam;

	cam.forward = normalized(op_minv(target, origin));
	cam.right = normalized(cross(forward, upguide));
	cam.up = cross(forward, upguide);

	cam.h = tan(fov);
	cam.w = h * aRatio;
}

t_ray		make_ray(t_camera cam, t_vector2 point) // t_point / vector2 ??
{
	t_vector direction;

	direction = cam.forward + point.u * cam.w * cam.right + point.v * cam.h * cam.up;
	return (set_ray(cam.origin, normalized(direction), RAY_T_MAX));
}
