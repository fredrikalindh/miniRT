/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:26:50 by frlindh           #+#    #+#             */
/*   Updated: 2020/02/07 14:43:15 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color		light_color(t_color l1, t_color l2, double d, double len)
{
	t_color			n;

	len == 0 ? len = 1 : 0;
	n.r = (double)(l1.r) + l2.r / sqrt(len) * d;
	n.g = (double)(l1.g) + l2.g / sqrt(len) * d;
	n.b = (double)(l1.b) + l2.b / sqrt(len) * d;
	// n.r = ft_min(255, n.r);
	// n.g = ft_min(255, n.g);
	// n.b = ft_min(255, n.b);
	// n.r = (double)(l1.r + l2.r) / sqrt(len) * d;
	// n.g = (double)(l1.g + l2.g) / sqrt(len) * d;
	// n.b = (double)(l1.b + l2.b) / sqrt(len) * d;
	return (n);
}

t_color		total_color(t_color l, t_color c)
{
	t_color			n;

	n.r = ft_min(l.r * c.r / 255, 255);
	n.g = ft_min(l.g * c.g / 255, 255);
	n.b = ft_min(l.b * c.b / 255, 255);
	return (n);
}

t_color		new_color(int r, int g, int b)
{
	t_color	c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color		same_color(int col)
{
	t_color	c;

	c.r = col;
	c.g = col;
	c.b = col;
	return (c);
}
