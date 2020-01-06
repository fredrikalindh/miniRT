/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:37:52 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/06 00:38:52 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


void	create_header(t_header *i)
{
	i->type = 0x4d42;
	i->size = g_rt.res_x * g_rt.res_y * 4 + 54;
	i->offset = 54;
	i->dib_header_size = 40;
	i->width_px = g_rt.res_x;
	i->height_px = g_rt.res_y;
	i->num_planes = 1;       // Number of color planes
	i->bits_per_pixel = 24;
	i->compression = 3;      // Compression type
	i->image_size = i->size - 54;
	i->x_resolution_ppm = 0; // Pixels per meter
	i->y_resolution_ppm = 0; // Pixels per meter
	i->num_colors = 0;       // Number of colors
	i->important_colors = 0; // Important colors
}

void		open_image()
{
	t_image img;

	if (!(g_rt.image = (char *)malloc(g_rt.res_x * g_rt.res_y * 4)))
		exit (-1);
	img.data = g_rt.image;
	ray_trace();
	create_header(&img.header);
	if ((g_rt.fd = open("./minirt.bmp", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU)) == -1)
		ft_puterr("failed to create image.bmp");
	write(g_rt.fd, &img.header, 54);
	write(g_rt.fd, img.data, img.header.image_size);
	if (close(g_rt.fd) == -1)
		ft_puterr("failed to close image");
	exit (1);
}

int		main()
{
	if ((g_rt.fd = open("~/Desktop/minirt.bmp", O_CREAT | O_WRONLY | O_APPEND, S_IRWXU) == -1)
		ft_puterr("failed to create image.bmp");
	create_header();
	if (!(close(fd)))
		ft_puterr("failed to close file");
}


FILE *f;
unsigned char *img = NULL;
int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int

img = (unsigned char *)malloc(3*w*h);
memset(img,0,3*w*h);

for(int i=0; i<w; i++)
{
    for(int j=0; j<h; j++)
    {
        x=i; y=(h-1)-j;
        r = red[i][j]*255;
        g = green[i][j]*255;
        b = blue[i][j]*255;
        if (r > 255) r=255;
        if (g > 255) g=255;
        if (b > 255) b=255;
        img[(x+y*w)*3+2] = (unsigned char)(r);
        img[(x+y*w)*3+1] = (unsigned char)(g);
        img[(x+y*w)*3+0] = (unsigned char)(b);
    }
}

unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
unsigned char bmppad[3] = {0,0,0};

bmpfileheader[ 2] = (unsigned char)(filesize    );
bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
bmpfileheader[ 4] = (unsigned char)(filesize>>16);
bmpfileheader[ 5] = (unsigned char)(filesize>>24);

bmpinfoheader[ 4] = (unsigned char)(       w    );
bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
bmpinfoheader[ 6] = (unsigned char)(       w>>16);
bmpinfoheader[ 7] = (unsigned char)(       w>>24);
bmpinfoheader[ 8] = (unsigned char)(       h    );
bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
bmpinfoheader[10] = (unsigned char)(       h>>16);
bmpinfoheader[11] = (unsigned char)(       h>>24);

f = fopen("img.bmp","wb");
fwrite(bmpfileheader,1,14,f);
fwrite(bmpinfoheader,1,40,f);
for(int i=0; i<h; i++)
{
    fwrite(img+(w*(h-i-1)*3),3,w,f);
    fwrite(bmppad,1,(4-(w*3)%4)%4,f);
}

free(img);
fclose(f);
