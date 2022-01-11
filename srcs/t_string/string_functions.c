/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 15:25:36 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/11 13:56:09 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_string(t_string *string, char *src, t_bool to_malloc)
{
	string->size = ft_strlen(src) + 1;
	string->max_size = string->size * 2;
	if (to_malloc != TRUE)
		return ;
	string->str = malloc(sizeof(char) * (string->max_size));
	if (!string->str)
		exit(-1);
	dup_string(string, src, 0);
}

void	reinit_string(t_string *string)
{
	int		i;

	i = 0;
	if (!string->str)
		return ;
	while (string->str[i])
		string->str[i++] = 0;
	free(string->str);
	string->str = 0;
	string->max_size = 0;
	string->size = 0;
}

void	realloc_string(t_string *string)
{
	t_string	dst;

	init_string(&dst, string->str, TRUE);
	dst.max_size = string->max_size;
	reinit_string(string);
	string->str = malloc(sizeof(char) * dst.max_size * 2);
	if (!string->str)
		exit(-1);
	string->max_size = dst.max_size * 2;
	dup_string(string, dst.str, 0);
	reinit_string(&dst);
}

void	dup_string(t_string *string, char *src, int index)
{
	int		i;

	i = 0;
	if (!src)
		return ;
	if (!string->str)
	{
		init_string(string, src, TRUE);
		return ;
	}
	while (string->max_size < ((string->size) + ft_strlen(src)))
		realloc_string(string);
	while (src[i])
		string->str[index++] = src[i++];
	string->str[index] = 0;
	string->size = ft_strlen(string->str) + 1;
}

void	replace_string(t_string *string, int index, char *replace_with,
			size_t rsize)
{
	t_string	save;

	init_string(&save, &string->str[rsize + index], TRUE);
	dup_string(string, replace_with, index);
	dup_string(string, save.str, index + ft_strlen(replace_with));
	reinit_string(&save);
}
