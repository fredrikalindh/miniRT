/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:32:00 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/12 15:53:51 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	vector_blank(t_vector *v)
{
	v->x = 0.0;
	v->y = 1.0;
	v->z = 0.0;
}

void	vector_cpy(t_vector *v, t_vector old)
{
	v->x = old.x;
	v->y = old.y;
	v->z = old.z;
}

void	vector_xyz(t_vector *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

void	vector_f(t_vector *v, float f)
{
	v->x = f;
	v->y = f;
	v->z = f;
}
