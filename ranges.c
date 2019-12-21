/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ranges.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 21:00:05 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/10 21:26:03 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_bool		outside_range(t_color c)
{
	if (c.r < 0 || c.r > 255 || c.g < 0 || c.g > 255 || c.b < 0 || c.b > 255)
		return (TRUE);
	return (FALSE);
}

t_bool		outside_range2(t_vector v)
{
	if (v.x < -1 || v.x > 1 || v.y < -1 || v.y > 1 || v.z < -1 || v.z > 1)
		return (TRUE);
	return (FALSE);
}