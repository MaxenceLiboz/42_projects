/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_iso.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 14:54:53 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/10 16:45:18 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
	1: Loop trought all the table
	2: Convert x, y and z from carthesian to isometric
	3: x, y and z need to evolve with the dist coefficient
	4: x and y have each a starting value added
*/
void	convert_to_iso(t_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < map->y_size)
	{
		x = 0;
		while (x < map->x_size)
		{
			map->tab[y][x].world.x = (map->tab[y][x].local.x
					- map->tab[y][x].local.y) * map->dist + map->startx;
			map->tab[y][x].world.z = map->tab[y][x].local.z
				* (1 + map->dist / 2) * 0.82;
			map->tab[y][x].world.y = ((map->tab[y][x].local.x
						+ map->tab[y][x].local.y) / 2) * map->dist + map->starty
				- map->tab[y][x].world.z;
			map->tab[y][x].world.color = map->tab[y][x].local.color;
			x++;
		}
		y++;
	}
}
