/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:08:39 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/10 14:37:29 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
	1: Create a window
	2: Parse the map recieved in params
	3: Create the image of the 3d map
	4: Put the image in the window
	5: Listen to key press
	6: Call loop to give your graphical os the control
	7: Free everything
*/
int	main(int argc, char **argv)
{
	t_program	fdf;

	if (argc < 2)
		return (0);
	fdf.win.height = 1000;
	fdf.win.width = 1000;
fdf.win.mlx = mlx_init();
	fdf.win.win = mlx_new_window(fdf.win.mlx, fdf.win.width, fdf.win.width,
			"FDF program");
	if (!map_parser(&fdf.map, argv[1], fdf.win))
		return (0);
	create_img(&fdf);
	fdf.img.x = 0;
	fdf.img.y = 0;
	mlx_put_image_to_window(fdf.win.mlx, fdf.win.win, fdf.img.img,
		fdf.img.x, fdf.img.y);
	mlx_hook(fdf.win.win, 2, 1L << 0, ft_hooks, &fdf);
	mlx_hook(fdf.win.win, 17, 1L << 2, close_win, &fdf);
	mlx_loop(fdf.win.mlx);
	free_tab(((void **)fdf.map.tab));
	return (0);
}
