/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 15:25:36 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/17 10:21:52 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_string(t_string *string, char *src, t_bool to_malloc, t_prg *prg)
{
	int		size;

	if (!src)
		size = 1;
	else
		size = ft_strlen(src) + 1;
	string->size = size;
	string->max_size = size * 2;
	if (to_malloc != TRUE)
		return ;
	string->str = ft_malloc(prg, sizeof(char) * (string->max_size));
	dup_string(string, src, 0, prg);
}

void	reinit_string(t_string *string)
{
	string->str = 0;
	string->max_size = 0;
	string->size = 0;
}

void	realloc_string(t_string *string, t_prg *prg)
{
	t_string	dst;

	init_string(&dst, string->str, TRUE, prg);
	dst.max_size = string->max_size;
	string->str = ft_malloc(prg, sizeof(char) * (dst.max_size * 2));
	string->max_size = dst.max_size * 2;
	dup_string(string, dst.str, 0, prg);
}

void	dup_string(t_string *string, char *src, int index, t_prg *prg)
{
	int		i;

	i = 0;
	if (!src)
	{
		init_string(string, "", TRUE, prg);
		return ;
	}
	if (!string->str)
	{
		init_string(string, src, TRUE, prg);
		return ;
	}
	while (string->max_size < ((string->size) + ft_strlen(src) + 1))
		realloc_string(string, prg);
	while (src[i])
		string->str[index++] = src[i++];
	string->str[index] = 0;
	string->size = ft_strlen(string->str) + 1;
}

/*
	Replace a part of the string by something else
	1:	String is the string that will have something replaced
	2:	Indexs table is indexs[0] => Where to start the replacement
						indexs[1] => How long is the str to replace
	3:	Replace with the char * variable, replace_with
*/
void	replace_string(t_string *string, int *indexs, char *replace_with,
			t_prg *prg)
{
	t_string	save;

	init_string(&save, &string->str[indexs[1] + indexs[0]], TRUE, prg);
	dup_string(string, replace_with, indexs[0], prg);
	dup_string(string, save.str, indexs[0] + ft_strlen(replace_with), prg);
}
