/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:28:23 by fredrika          #+#    #+#             */
/*   Updated: 2019/11/26 13:22:28 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef	struct		s_param
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		key;
}					t_param;

int deal_key(int key, t_param *param)
{
	printf("%d\n", key);
	param->key = key;
	if (key == 53 || key == 8)
	{
		mlx_destroy_window(param->mlx_ptr, param->win_ptr);
		param->mlx_ptr = NULL;
		param->win_ptr = NULL;
		exit (0);
	}
	return (0);
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	int x;
	int y;
	int c;
	char *str;
	t_param	param;

	if (!(mlx_ptr = mlx_init()))
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "miniRT");
	y = 200;
	c = (16711680 * 1/*r*/ + 65280 * 1/*g*/ + 255 * 1/*b*/);
	while (--y >= 100)
	{
		x = 400;
		while (--x > 100)
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, c);
	}
	mlx_string_put(mlx_ptr, win_ptr, 180, 155, 255, "fredrika's program");
	param.mlx_ptr = mlx_ptr;
	param.win_ptr = win_ptr;
	mlx_key_hook(win_ptr, deal_key, (void *)&param);
	if (param.key == 53 || param.key == 8)
		exit (0);
	mlx_loop(mlx_ptr);
	return 0;
}
