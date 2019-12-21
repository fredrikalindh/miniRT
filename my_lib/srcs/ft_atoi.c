/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:12:46 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/03 15:09:36 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int		ft_atoi(char *str)
{
	int n;

	n = 0;
	while (str && *str)
		n = n * 10 + *str++ - '0';
	return (n);
}