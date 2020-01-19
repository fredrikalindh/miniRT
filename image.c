/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:37:52 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/19 13:31:59 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	header(unsigned char *fileh, unsigned char *infoh, int w, int h)
{
	int		fs;

	fs = 54 + 3 * w * h;
	fileh[2] = (unsigned char)(fs);
	fileh[3] = (unsigned char)(fs >> 8);
	fileh[4] = (unsigned char)(fs >> 16);
	fileh[5] = (unsigned char)(fs >> 24);
	infoh[4] = (unsigned char)(w);
	infoh[5] = (unsigned char)(w >> 8);
	infoh[6] = (unsigned char)(w >> 16);
	infoh[7] = (unsigned char)(w >> 24);
	infoh[8] = (unsigned char)(h);
	infoh[9] = (unsigned char)(h >> 8);
	infoh[10] = (unsigned char)(h >> 16);
	infoh[11] = (unsigned char)(h >> 24);
}

void		open_image(int w, int h, int i)
{
	t_image	g;

	if ((g_rt.fd = open(g_rt.name, O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
		ft_puterr("failed to create miniRT.bmp");
	if (!(g_rt.image = (char *)malloc(w * h * 3)))
		exit(-1);
	write(1, "\033[1;36mCreating image... \033[0m", 29);
	ray_trace();
	g.data = g_rt.image;
	g.f = (unsigned char[14]){'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
	g.i = (unsigned char[40]){40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
	g.bmppad = (unsigned char[3]){0, 0, 0};
	header(g.f, g.i, w, h);
	write(g_rt.fd, g.f, 14);
	write(g_rt.fd, g.i, 40);
	while (++i < h)
	{
		write(g_rt.fd, g.data + w * 3 * (h - i - 1), w * 3);
		write(g_rt.fd, g.bmppad, (4 - (w * 3) % 4) % 4);
	}
	if (close(g_rt.fd) == -1)
		ft_puterr("failed to close image");
	free(g.data);
	write(1, "\033[1;36mdone!\n\033[0m", 17);
	exit(1);
}
