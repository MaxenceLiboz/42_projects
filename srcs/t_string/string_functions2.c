/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:34:57 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/19 13:58:58 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_string	sub_string(char *src, size_t start, size_t size, t_list **mem)
{
	t_string	string;
	char		*dst;

	dst = ft_substr(src, start, size);
	if (!dst)
		ft_error_free(mem);
	init_string(&string, dst, TRUE, mem);
	free(dst);
	return (string);
}

void	erase_string(t_string *string, char *to_replace, size_t start,
	t_list **mem)
{
	t_string	temp;

	init_string(&temp, &string->str[start + ft_strlen(to_replace)], TRUE, mem);
	dup_string(string, temp.str, start, mem);
}

void	add_string(t_string *string, char *to_add, size_t index, t_list **mem)
{
	t_string	temp;

	init_string(&temp, &string->str[index], TRUE, mem);
	dup_string(string, to_add, 0, mem);
	dup_string(string, temp.str, string->size - 1, mem);
}
