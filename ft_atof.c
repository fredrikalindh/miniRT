/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:11:41 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/03 15:09:40 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

double	ft_atof(char *str)
{
	double f;
	double div;
	double neg;

	f = 0.0;
	neg = 1.0;
	if (str && *str == '-')
	{
		neg = -1.0;
		str++;
	}
	while (str && *str && *str != '.' && *str >= '0' && *str <= '9')
		f = f * 10 + *str++ - '0';
	div = 0.1;
	while (str && *(++str) && *str >= '0' && *str <= '9')
	{
		f += ((*str - '0') * div);
		div /= 10.0;
	}
	return (f * neg);
}
