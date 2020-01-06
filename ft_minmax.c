/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:31:00 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/06 14:11:41 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int		ft_min(int a, int b)
{
	return (a < b) ? a : b;
}

int		ft_max(int a, int b)
{
	return (a > b) ? a : b;
}

double	ft_mind(double a, double b)
{
	return (a < b) ? a : b;
}

double	ft_maxd(double a, double b)
{
	return (a > b) ? a : b;
}
