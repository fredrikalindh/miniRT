/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:28:23 by fredrika          #+#    #+#             */
/*   Updated: 2019/11/25 17:35:06 by fredrikalindh    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>

int deal_key(int key, void *param)
{
//	if (key == 12 || key == 256)
//		return (1);
	return (0);
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	int x;
	int y;
	int ret;

	x = y = 2000;
	if (!(mlx_ptr = mlx_init()))
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, x, y, "image.bmp");
	mlx_pixel_put(mlx_ptr, win_ptr, 0, 0, 65354);
	ret = 0;
	mlx_loop(mlx_ptr);
	ret = mlx_key_hook(win_ptr, deal_key,(void *) 0);
	return 0;
}
