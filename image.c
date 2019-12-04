/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:37:52 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/04 20:12:25 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Bitmap file header	14 bytes:
2: BA
4: The size of the BMP file in bytes = x * y * 4
2: value depends on app
2: value depends on app
4: offset = starting address, of the byte where the bitmap image data (pixel array) can be found
*/
//Pixel array

void	create_header()
{
	int size;

	size = g_rt.res_x * g_rt.res_y * 4;
	write(g_rt.fd, "BA", 2);
	ft_putnbr_fd(size, g_rt.fd);
	write(g_rt.fd, "miniRT", 4);
	ft_putnbr_fd(15, g_rt.fd); // ?
}

int		main()
{
	if ((g_rt.fd = open("~/Desktop/minirt.bmp", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU) == -1)
		ft_puterr("failed to create image.bmp");
	create_header();
	if (!(close(fd)))
		ft_puterr("failed to close file");
}
