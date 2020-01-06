/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:26:50 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/06 14:11:07 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

t_color		color_add(t_color c1, t_color c2) // ADD MORE OPERATORS
{
	return (new_color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b));
}

t_color		color_mult(t_color c1, double f) // ADD MORE OPERATORS
{
	return (new_color(c1.r * f, c1.g * f, c1.b * f));
}
