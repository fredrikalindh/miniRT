/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:37:52 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/01 22:00:42 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>


// t_vector	compute_ray(int x, int y)
// {
// 	t_ray ray;
// 	double w;
// 	double h;
// 	double h;
//
// 	w = g_rt.res_x / 2 - x;
// 	h = g_rt.res_y / 2 - y;
// 	ray.origin = g_rt.camera.position; //?
// 	ray.direction = sinh(sqrt(w * w + h * h));
// }

int main()
{
	int actualWindow;
	GetWindowRect(GetDesktopWindow(), &actualDesktop);
	printf("%d\n", actualWindow);
}



/*Bitmap file header	14 bytes:
2: BA
4: The size of the BMP file in bytes = x * y * 4
2: value depends on app
2: value depends on app
4: offset = starting address, of the byte where the bitmap image data (pixel array) can be found
*/
//Pixel array
//
// void ft_putchar_fd(char c, int fd)
// {
// 	write(fd, &c, 1);
// }
//
// void	ft_putnbr_fd(int n, int fd)
// {
// 	if (n == -2147483648)
// 	{
// 		write(fd, "-2", 2);
// 		n = 147483648;
// 	}
// 	if (n < 0)
// 	{
// 		write(fd, "-", 1);
// 		n = -n;
// 	}
// 	if (n < 10)
// 		ft_putchar_fd(n + '0', fd);
// 	if (n >= 10)
// 	{
// 		ft_putnbr_fd(n / 10, fd);
// 		ft_putchar_fd('0' + n % 10, fd);
// 	}
// }
//
// void	create_header(int fd)
// {
// 	int size;
// 	int x;
//
// 	size = 400 * 400 * 4;
// 	write(fd, "BA", 2);
// 	ft_putnbr_fd(size, fd);
// 	// write(fd, "miniRT", 4);
// 	ft_putnbr_fd(15, fd); // ?
// 	for (x = 0; x < 400 * 400; x++)
// 	{
// 		write(fd, "255", 3);
// 	}
// }
//
// int		main()
// {
// 	int fd;
// 	char buf[100];
// 	int ret;
//
// 	fd = open("~/Desktop/minirt.bmp", O_CREAT | O_RDWR, S_IRWXU);
// 		// ft_puterr("failed to create image.bmp");
// 	create_header(fd);
// 	ret = read(fd, buf, 100);
// 	buf[ret] = '\0';
// 	printf("%d %s\n", ret, buf);
// 	// ray_trace();
// 	close(fd);
// 		// ft_puterr("failed to close file");
// }
