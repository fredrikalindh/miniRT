/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vectors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:47:35 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/12 16:48:01 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void op_plus(t_vector *v, t_vector op)
{
	v->x += op.x;
	v->y += op.y;
	v->z += op.z;
}

void op_min(t_vector *v, t_vector op)
{
	v->x -= op.x;
	v->y -= op.y;
	v->z -= op.z;
}

void op_mult(t_vector *v, t_vector op)
{
	v->x *= op.x;
	v->y *= op.y;
	v->z *= op.z;
}

void op_mult_f(t_vector *v, float f)
{
	v->x *= f;
	v->y *= f;
	v->z *= f;
}

void op_div(t_vector *v, t_vector op)
{
	v->x /= op.x;
	v->y /= op.y;
	v->z /= op.z;
}

void op_div_f(t_vector *v, float f)
{
	v->x /= f;
	v->y /= f;
	v->z /= f;
}

void op_neg(t_vector *v) //WORKING ?
{
	v->x = -v->x;
	v->y = -v->y;
	v->z = -v->z;
}
