/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranges.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 21:00:05 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/13 17:28:37 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		outside_range(t_color c)
{
	if (c.r < 0 || c.r > 255 || c.g < 0 || c.g > 255 || c.b < 0 || c.b > 255)
		return (1);
	return (0);
}

int		outside_range2(t_vector v)
{
	if (v.x < -1 || v.x > 1 || v.y < -1 || v.y > 1 || v.z < -1 || v.z > 1)
		return (1);
	return (0);
}

int		outside_range3(double d)
{
	if (d < 0 || d > 1)
		return (1);
	return (0);
}
