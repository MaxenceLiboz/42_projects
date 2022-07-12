/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:27:59 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/10 14:35:26 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
	1: keycode == 53 => escape
	2: Destroy the window
	3: free everything
	4: end the program
*/
int	close_win(t_program *fdf)
{
	mlx_destroy_window(fdf->win.mlx, fdf->win.win);
	free_tab(((void **)fdf->map.tab));
	exit(1);
	return (1);
}

/*
	keycode == 126 => up
	keycode == 125 => down
	keycode == 123 => left
	keycode == 124 => right
	1: For each keycode press move on the position related to the arrow.
	2: Add some condition to never let the image leave the entire screen
*/
static int	move(int keycode, t_program *fdf)
{
	if (keycode == 126
		&& fdf->map.tab[fdf->map.y_size - 1][fdf->map.x_size - 1].world.y
		+ fdf->img.y > 200)
		fdf->img.y -= 5;
	else if (keycode == 125
		&& (fdf->map.tab[0][0].world.y > 0
		|| fdf->img.y != 0)
		&& fdf->map.tab[0][0].world.y + fdf->img.y < 800)
		fdf->img.y += 5;
	else if (keycode == 123
		&& fdf->map.tab[0][fdf->map.x_size - 1].world.x + fdf->img.x > 200)
		fdf->img.x -= 5;
	else if (keycode == 124
		&& (fdf->map.tab[fdf->map.y_size - 1][0].world.x > 0
		|| fdf->img.x != 0)
		&& fdf->map.tab[fdf->map.y_size - 1][0].world.x + fdf->img.x < 800)
		fdf->img.x += 5;
	else
		return (0);
	return (1);
}

/*
	keycode == 6 => z
	keycode == 5 => x
	1: With z pressed zoom the map
	2: With x pressed unzoom the map
	3: Add condition to have maximum and minimum zoom / unzoom
*/
static int	zoom(int keycode, t_program *fdf)
{
	if (keycode == 6
		&& fdf->map.dist < 1.5 * fdf->win.width / fdf->map.x_size)
	{
		fdf->map.dist += 0.5;
		fdf->img.x = 0;
		fdf->img.y = 0;
	}
	else if (keycode == 7
		&& fdf->map.dist > fdf->win.width / fdf->map.x_size / 4
		&& fdf->map.dist > 1)
	{
		fdf->map.dist -= 0.5;
		fdf->img.x = 0;
		fdf->img.y = 0;
	}
	else
		return (0);
	return (1);
}

/*
	1: Call functions to move or zoom the image
	2: if the image need to move, destroy the old one and create a new one
	3: else do nothing
*/
static int	move_image(int keycode, t_program *fdf)
{
	if (move(keycode, fdf) || zoom(keycode, fdf))
	{
		mlx_destroy_image(fdf->win.mlx, fdf->img.img);
		create_img(fdf);
		mlx_put_image_to_window(fdf->win.mlx, fdf->win.win, fdf->img.img,
			fdf->img.x, fdf->img.y);
	}
	return (1);
}

/*
	1: Each time a key is pressed call functions that are going to interact
	   with the program
*/
int	ft_hooks(int keycode, t_program *fdf)
{
	if (keycode == 53)
		close_win(fdf);
	move_image(keycode, fdf);
	return (1);
}
