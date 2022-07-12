/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:37:46 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/10 14:35:16 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <mlx.h>
# include <stdio.h>
# include <math.h>
# define BASE16 "0123456789abcdef"

typedef struct s_v4
{
	double	x;
	double	y;
	double	z;
	int		color;

}	t_v4;

typedef struct s_vertex
{
	t_v4	local;
	t_v4	world;
}	t_vertex;

typedef struct s_map
{
	t_vertex	**tab;
	int			x_size;
	int			y_size;
	double		dist;
	double		startx;
	double		starty;
}	t_map;

typedef struct s_win
{
	void	*mlx;
	void	*win;
	int		height;
	int		width;
}	t_win;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		x;
	int		y;
}	t_data;

typedef struct s_program
{
	t_win	win;
	t_map	map;
	t_data	img;
}	t_program;

int		map_parser(t_map *map, char *filename, t_win win);
int		free_tab(void **tab);
int		rperror(char *str, int return_value);
void	convert_to_iso(t_map *map);
int		ft_hooks(int keycode, t_program *fdf);
int		close_win(t_program *fdf);
void	create_img(t_program *fdf);

#endif