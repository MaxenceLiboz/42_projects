/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 08:25:09 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/10 16:45:57 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
	1: Draw the pixel inside the image
	2: Add the color of the pixel
	3: The addr is a simple table, we can then access the y by multiplying with
	   the lenght of a line, and add the x to it. 
	4: To get the position of x multiply it by the number of bits by pixels and
	   knowing that one bits is equal to 8 => divide it by 8.
*/
static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		pixel;

	pixel = (y * data->line_length + x * (data->bits_per_pixel / 8));
	if (pixel < 0)
		return ;
	dst = data->addr + pixel;
	*(unsigned int *)dst = color;
}

/*
	1: Calculate the dx and dy
	2: Caluclate the hypothenuses length thanks to pythagore theoreme
	3: Draw each pixels of the hypothenuses in the image
*/
static void	drawline(t_program *fdf, t_v4 p0, t_v4 p1)
{
	double	dx;
	double	dy;
	int		dcolor;
	int		pixels;

	dx = p1.x - p0.x;
	dy = p1.y - p0.y;
	dcolor = p1.color - p0.color;
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;
	dcolor /= pixels * 8;
	while (pixels)
	{
		my_mlx_pixel_put(&fdf->img, p0.x, p0.y, p0.color);
		p0.x += dx;
		p0.y += dy;
		p0.color += dcolor;
		pixels--;
	}
}

/*
	1: Check if the point can be draw
	2: Check if the next point can be draw
	3: Drawline both vertical and horizontal
*/
static void	check_pixel_put(t_program *fdf, int x, int y)
{
	if (!(fdf->map.tab[y][x].world.x < 0 - fdf->img.x
		|| fdf->map.tab[y][x].world.x > fdf->win.width - fdf->img.x
		|| fdf->map.tab[y][x].world.y < 0 - fdf->img.y
		|| fdf->map.tab[y][x].world.y > fdf->win.height - fdf->img.y))
	{
		if (x < fdf->map.x_size - 1
			&& (!(fdf->map.tab[y][x + 1].world.x < 0 - fdf->img.x
				|| fdf->map.tab[y][x + 1].world.x > fdf->win.width - fdf->img.x
			|| fdf->map.tab[y][x + 1].world.y < 0 - fdf->img.y
			|| fdf->map.tab[y][x + 1].world.y > fdf->win.height - fdf->img.y)))
			drawline(fdf, fdf->map.tab[y][x].world,
				fdf->map.tab[y][x + 1].world);
		if (y < fdf->map.y_size - 1
			&& (!(fdf->map.tab[y + 1][x].world.x < 0 - fdf->img.x
				|| fdf->map.tab[y + 1][x].world.x > fdf->win.width - fdf->img.x
			|| fdf->map.tab[y + 1][x].world.y < 0 - fdf->img.y
			|| fdf->map.tab[y + 1][x].world.y > fdf->win.height - fdf->img.y)))
			drawline(fdf, fdf->map.tab[y][x].world,
				fdf->map.tab[y + 1][x].world);
	}
}

/*
	1: Convert all the carthesian points to isometric
	2: Loop trought all the table and check if the pixel can be draw
*/
static void	fill_image(t_program *fdf)
{
	int		x;
	int		y;

	y = 0;
	convert_to_iso(&fdf->map);
	while (y < fdf->map.y_size)
	{
		x = 0;
		while (x < fdf->map.x_size)
		{
			check_pixel_put(fdf, x, y);
			x++;
		}
		y++;
	}
}

/*
	1: Calculate the width and height of the image in order to be able to zoom in
	2: Create a new image and get the address
	3: Fill the image with the map value
*/
void	create_img(t_program *fdf)
{
	int		width;
	int		height;

	width = 8 * fdf->map.x_size * fdf->map.dist;
	height = 8 * fdf->map.y_size * fdf->map.dist;
	fdf->img.img = mlx_new_image(fdf->win.mlx, width, height);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel,
			&fdf->img.line_length, &fdf->img.endian);
	fill_image(fdf);
}
