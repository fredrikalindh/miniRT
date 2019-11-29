/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:15:25 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/29 15:13:20 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		ray_trace()
{
	int x;
	int y;

	y = -1;
	while (++y <= g_rt.res_y)
	{
		x = -1;
		while (++x <= g_rt.res_x)
		{
			shootRay();
			*g_rt.image++ = (unsigned char)g_rt.intersection.color.b;
			*g_rt.image++ = (unsigned char)g_rt.intersection.color.g;
			*g_rt.image++ = (unsigned char)g_rt.intersection.color.r;
			g_rt.image++;
	}
}
