/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:51:58 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/20 19:05:18 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_puterr(char *str)
{
	write(2, "\033[1;31mError: ", 14);
	write(2, str, ft_strlen(str));
	write(2, "\n\033[0m", 5);
	free_globals(NULL, g_rt.camera);
	exit(-1);
}
