/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:47:35 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/19 13:32:56 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_vector	op_min(t_vector v, t_vector op)
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

t_vector	op_mult_f(t_vector v, double f)
{
	v.x *= f;
	v.y *= f;
	v.z *= f;
	return (v);
}
