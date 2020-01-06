/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:26:50 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/10 20:15:28 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	clamp(t_color *c) // edit if min max aren't 0 255
{
	c->r < 0 ? c->r = 0 : 0;
	c->r > 255 ? c->r = 255 : 0;
	c->g < 0 ? c->g = 0 : 0;
	c->g > 255 ? c->g = 255 : 0;
	c->b < 0 ? c->b = 0 : 0;
	c->b > 255 ? c->b = 255 : 0;
}

void	apply_gamma(t_color *c, double exposure, double gamma) // 2.2
{
	c->r = pow(c->r * exposure, gamma);
	c->g = pow(c->g * exposure, gamma);
	c->b = pow(c->b * exposure, gamma);
}

int		ret_color(t_color c)
{
	return(c.r * 65536 + c.g * 256 + c.b);
}

t_color	new_color(int r, int g, int b)
{
	t_color c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_color	same_color(int col)
{
	t_color c;

	c.r = col;
	c.g = col;
	c.b = col;
	return (c);
}

t_color	color_add(t_color c1, t_color c2) // ADD MORE OPERATORS
{
	return (new_color(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b));
}

t_color	color_mult(t_color c1, double f) // ADD MORE OPERATORS
{
	return (new_color(c1.r * f, c1.g * f, c1.b * f));
}
