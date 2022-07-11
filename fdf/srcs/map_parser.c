/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 10:43:50 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/09 09:49:41 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
	Count the number of int inside a line to get the x size;
*/
static int	ft_count_int(const char *str, char charset)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] && str[i] == charset)
		i++;
	if (str[i] != 0)
		count++;
	while (str[i])
	{
		if (str[i] == charset
			&& (str[i + 1] != charset && str[i + 1] != 0 && str[i + 1] != '\n'))
			count++;
		i++;
	}
	return (count);
}

/*
	1: Get x size;
	2: Get y size;
	3: If during the y size loop, any of the x is different that the first
	   return an error;
*/
static int	get_sizes(t_map *map, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	map->x_size = ft_count_int(line, ' ');
	while (line)
	{
		map->y_size += 1;
		free(line);
		line = get_next_line(fd);
		if (line && map->x_size != ft_count_int(line, ' '))
			return (0);
	}
	close(fd);
	return (1);
}

/*
	1: Malloc the number of t_vertex in a line;
	2: Set the color white as default;
	3: For each t_vertex, add the x, z, y and color;
	4: If there is any problem free and return 0 else return 1;
*/
static int	vertex_line_parser(t_map *map, char **str, int y)
{
	int		x;
	int		i;

	x = 0;
	map->tab[y] = malloc(sizeof(t_vertex) * (map->x_size));
	if (!map->tab[y])
		return (0);
	i = 0;
	while (i < map->x_size)
		map->tab[y][i++].local.color = 0xFFFFFF;
	while (x < map->x_size)
	{
		i = 0;
		map->tab[y][x].local.x = x;
		map->tab[y][x].local.y = y;
		map->tab[y][x].local.z = ft_atoi(str[x]);
		while (str[x][i] != ',' && str[x][i])
			i++;
		if (str[x][i] == ',')
			map->tab[y][x].local.color = ft_atoi_base(str[x] + i + 1, BASE16);
		x++;
	}
	return (1);
}

/*
	1: Open fd;
	2: Get the split of each line until the end of the file;
	3: Send this char ** to vertex_line_parser;
*/
static int	vertex_parser(t_map *map, char *filename)
{
	int		fd;
	char	**str;
	char	*gnl;
	int		y;

	y = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free_tab((void **)map->tab));
	gnl = get_next_line(fd);
	str = ft_split(gnl, ' ');
	free(gnl);
	while (str)
	{
		if (!vertex_line_parser(map, str, y))
			return (free_tab((void **)map->tab));
		free_tab((void **)str);
		gnl = get_next_line(fd);
		str = ft_split(gnl, ' ');
		free(gnl);
		y++;
	}
	map->tab[y] = NULL;
	return (1);
}

/*
	1: Get all the sizes (x and y);
	2: Calculate the distance and both x and y starting points
	3: Malloc the t_vertex **;
	4: Parse the lines of vertex;
	5: If there is any problem return 0 else return 1;
*/
int	map_parser(t_map *map, char *filename, t_win win)
{
	map->x_size = 0;
	map->y_size = 0;
	if (!get_sizes(map, filename))
		return (rperror("Wrong sizes", 0));
	if ((win.width / map->x_size + win.height / map->y_size) / 2 / 3 > 1)
		map->dist = (((win.width / map->x_size) + (win.height / map->y_size))
				/ 2) / 3;
	else
		map->dist = 1;
	map->startx = win.width / 2;
	map->starty = win.height / 3;
	map->tab = (t_vertex **)malloc(sizeof(t_vertex *) * (map->y_size + 1));
	if (!map->tab)
		return (rperror("Malloc returned 0", 0));
	if (!vertex_parser(map, filename))
		return (rperror("Malloc returned 0", 0));
	return (1);
}
