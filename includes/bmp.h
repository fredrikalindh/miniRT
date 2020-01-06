/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 19:01:20 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/06 12:39:19 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

// typedef struct s_header {
// 	unsigned int	type:16;             // Magic identifier: 0x4d42
// 	unsigned char	size1;             // File size in bytes
// 	unsigned char	size2;             // File size in bytes
// 	unsigned char	size3;             // File size in bytes
// 	unsigned char	size4;             // File size in bytes
// 	unsigned int	reserved1:16;        // Not used
// 	unsigned int	reserved2:16;        // Not used
// 	unsigned int	offset:32;       // Offset to image data in bytes from beginning of file (54 bytes)
// 	unsigned int	dib_header_size:32;  // DIB Header size in bytes (40 bytes)
// 	int				width_px:32;         // Width of the image
// 	int				height_px:32;        // Height of image
// 	unsigned int	num_planes:16;       // Number of color planes
// 	unsigned int	bits_per_pixel:16;   // Bits per pixel
// 	unsigned int	compression:32;      // Compression type
// 	unsigned int	image_size:32; // Image size in bytes
// 	int				x_resolution_ppm:32; // Pixels per meter
// 	int				y_resolution_ppm:32; // Pixels per meter
// 	unsigned int	num_colors:32;       // Number of colors
// 	unsigned int	important_colors:32; // Important colors
// }	t_header;

// typedef struct s_header {
// 	unsigned int file_type:16;     // File type always BM which is 0x4D42
// 	unsigned int file_size:32;     // Size of the file (in bytes)
// 	unsigned int reserved1:16;     // Reserved, always 0
// 	unsigned int reserved2:16;     // Reserved, always 0
// 	unsigned int offset_data:32;   // Start position of pixel data in bytes
// }		t_header;

typedef struct s_image {
	unsigned char		*fileh;
	unsigned char		*infoh;
	unsigned char		*bmppad;
	char*				data;
}	t_image;

#endif
