/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:37:42 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/12 00:34:06 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_command(t_command *array_string, int size, int to_malloc)
{
	array_string->size = size;
	array_string->max_size = size;
	if (to_malloc != TRUE)
		return ;
	array_string->array = malloc(sizeof(t_string) * size);
	if (!array_string->array)
		exit(-1);
}

void	reinit_command(t_command *array)
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
	array->index = 0;
	array->size = 0;
}
