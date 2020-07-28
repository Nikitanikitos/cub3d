/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <imicah@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 22:28:08 by imicah            #+#    #+#             */
/*   Updated: 2020/07/27 22:28:09 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_bitmap_file_header	file_header_init(int file_size)
{
	t_bitmap_file_header	bmp_file_header;

	bmp_file_header.bitmap_type[0] = 'B';
	bmp_file_header.bitmap_type[1] = 'M';
	bmp_file_header.file_size = file_size;
	bmp_file_header.reserved1 = 0;
	bmp_file_header.reserved2 = 0;
	bmp_file_header.offset_bits = 0;
	return (bmp_file_header);
}

t_bitmap_image_header	image_header_init(int width, int height, int file_size)
{
	t_bitmap_image_header	bmp_image_header;

	bmp_image_header.size_header = sizeof(bmp_image_header);
	bmp_image_header.width = width;
	bmp_image_header.height = height;
	bmp_image_header.planes = 1;
	bmp_image_header.bit_count = 24;
	bmp_image_header.compression = 0;
	bmp_image_header.image_size = file_size;
	bmp_image_header.ppm_x = 3780;
	bmp_image_header.ppm_y = 3780;
	bmp_image_header.clr_used = 0;
	bmp_image_header.clr_important = 0;
	return (bmp_image_header);
}

void 					pixel_put(FILE *image, int image_size, char *data)
{
	char	color[3];
	int 	i;

	i = 0;
	while (i < image_size)
	{
		color[0] = data[i + 1];
		color[1] = data[i + 2];
		color[2] = data[i + 3];
		fwrite(color, 1, sizeof(color), image);
		i += 4;
	}
}

void					save_bmp(int width, int height, char *data)
{
	FILE					*image;
	t_bitmap_file_header	bmp_file_header;
	t_bitmap_image_header	bmp_image_header;
	const int				image_size = width * height;
	const int				file_size = 54 + 4 * image_size;

	bmp_file_header = file_header_init(file_size);
	bmp_image_header = image_header_init(width, height, file_size);
	image = fopen("Cub3D.bmp", "wb");
	fwrite(&bmp_file_header, 1, 14, image);
	fwrite(&bmp_image_header, 1, sizeof(bmp_image_header), image);
	pixel_put(image, image_size * 4, data);
	fclose(image);
}
