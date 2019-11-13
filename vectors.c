/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:32:00 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/13 13:10:34 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	vector_blank()
{
	t_vector v;

	v.x = 0.0;
	v.y = 1.0;
	v.z = 0.0;
	return (v);
}

t_vector	vector_cpy(t_vector old)
{
	t_vector v;

	v.x = old.x;
	v.y = old.y;
	v.z = old.z;
	return (v);
}

t_vector	vector_xyz(float x, float y, float z)
{
	t_vector v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vector	vector_f(float f)
{
	t_vector v;

	v.x = f;
	v.y = f;
	v.z = f;
	return (v);
}
