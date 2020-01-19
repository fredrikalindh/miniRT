/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 17:28:23 by fredrika          #+#    #+#             */
/*   Updated: 2020/01/19 13:32:16 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		main(int ac, char *av[])
{
	t_param		p;

	init_scene(ac, av);
	if (g_rt.save == 1)
		open_image(g_rt.res_x, g_rt.res_y, -1);
	if (!(p.mlx_ptr = mlx_init()))
		ft_puterr("couldn't init MLX");
	p.bpp = 32;
	p.sl = g_rt.res_x * 32;
	p.endian = 1;
	p.img_ptr = mlx_new_image(p.mlx_ptr, g_rt.res_x, g_rt.res_y);
	g_rt.image = mlx_get_data_addr(p.img_ptr, &p.bpp, &p.sl, &p.endian);
	g_rt.select.origin = &g_rt.camera->pos;
	g_rt.select.dir = &g_rt.camera->dir;
	write(1, "\033[1;36mRendering image...\n\033[0m", 30);
	ray_trace();
	p.win_ptr = mlx_new_window(p.mlx_ptr, g_rt.res_x, g_rt.res_y, "minirt");
	mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img_ptr, 0, 0);
	mlx_key_hook(p.win_ptr, deal_key, (void *)&p);
	mlx_mouse_hook(p.win_ptr, deal_mouse, (void *)&p);
	mlx_hook(p.win_ptr, X_BUTT, 0, exit_program, (void *)&p);
	mlx_loop(p.mlx_ptr);
}
