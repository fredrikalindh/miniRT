/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:47:35 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/06 20:19:57 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	op_add(t_vector v, t_vector op)
{
	v.x += op.x;
	v.y += op.y;
	v.z += op.z;

	return (v);
}

void		op_addp(t_vector *v, t_vector op)
{
	v->x += op.x;
	v->y += op.y;
	v->z += op.z;
}

t_vector op_min(t_vector v, t_vector op)
{
	v.x -= op.x;
	v.y -= op.y;
	v.z -= op.z;

	return (v);
}

void		op_minv(t_vector *v, t_vector op)
{
	v->x -= op.x;
	v->y -= op.y;
	v->z -= op.z;
}

void		op_mult(t_vector *v, t_vector op)
{
	v->x *= op.x;
	v->y *= op.y;
	v->z *= op.z;
}

t_vector	op_mult_f(t_vector v, double f)
{
	v.x *= f;
	v.y *= f;
	v.z *= f;

	return (v);
}

void		op_div(t_vector *v, t_vector op)
{
	v->x /= op.x;
	v->y /= op.y;
	v->z /= op.z;
}

void		op_div_f(t_vector *v, double f)
{
	v->x /= f;
	v->y /= f;
	v->z /= f;
}

void		op_neg(t_vector *v) //WORKING ?
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
}
