/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:34:57 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/11 13:28:47 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sub_string(t_string *string, char *src, size_t start, size_t size)
{
	char	*dst;

	dst = ft_substr(src, start, size);
	dup_string(string, dst, 0);
	free(dst);
}

void	erase_string(t_string *string, char *to_replace, size_t start)
{
	t_string	temp;

	init_string(&temp, &string->str[start + ft_strlen(to_replace)], TRUE);
	dup_string(string, temp.str, start);
	reinit_string(&temp);
}

void	add_string(t_string *string, char *to_add, size_t index)
{
	t_string	temp;

	init_string(&temp, &string->str[index], TRUE);
	dup_string(string, to_add, 0);
	dup_string(string, temp.str, string->size - 1);
	reinit_string(&temp);
}
