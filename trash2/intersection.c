/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:58:45 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/13 13:06:45 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_intersection intersection_blank()
{
	t_intersection i;

	i.ray = 0;
	i.t = RAY_T_MAX;
	i.shape = NULL;
	i.color = 0; //??????????????
	return (i);
}

t_intersection intersection_cpy(t_intersection old)
{
	t_intersection i;

	i.ray = old.ray;
	i.t = old.t;
	i.shape = old.shape;
	i.color = old.color; //??????????????
	return (i);
}

t_intersection intersection_ray(t_ray ray)
{
	t_intersection i;

	i.ray = ray.ray;
	i.t = ray.t;
	i.shape = NULL;
	i.color = 0; //??????????????
	return (i);
}
