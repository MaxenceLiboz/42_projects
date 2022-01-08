/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_string_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:37:42 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/08 15:25:16 by maxencelibo      ###   ########.fr       */
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
