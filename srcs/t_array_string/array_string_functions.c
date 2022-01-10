/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_string_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:37:42 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/10 12:56:45 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_array_string(t_array_string *array_string, int size, int to_malloc)
{
	array_string->size = size;
	array_string->max_size = size;
	if (to_malloc != TRUE)
		return ;
	array_string->array = malloc(sizeof(t_string) * size);
	if (!array_string->array)
		exit(-1);
}

void	reinit_array_string(t_array_string *array)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (!array->array)
		return ;
	while (y < array->max_size)
		reinit_string(&array->array[y++]);
	free(array->array);
	reinit_string(&array->command);
	array->max_size = 0;
	array->size = 0;
}
