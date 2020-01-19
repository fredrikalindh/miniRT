/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 15:33:02 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/19 13:32:11 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_lights(void)
{
	static t_light	*l = NULL;

	if (l == NULL)
		l = g_rt.light;
	g_rt.select.origin = &l->coor;
	g_rt.select.dir = NULL;
	g_rt.select.r = &l->bright;
	g_rt.select.h = NULL;
	l = l->next;
}
