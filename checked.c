/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checked.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:05:23 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/19 13:32:00 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		checked(double u, double v, t_color c)
{
	(u < 0) ? u = (fabs(u) + 1) : 0;
	(v < 0) ? v = (fabs(v) + 1) : 0;
	if ((int)u % 2 != (int)v % 2)
		return (new_color(255 - c.r, 255 - c.g, 255 - c.b));
	return (c);
}
