/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:34:57 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/16 12:02:56 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_string	sub_string(char *src, size_t start, size_t size, t_list **mem)
{
	t_string	string;
	char		*dst;

	dst = ft_substr(src, start, size);
	if (!dst)
		ft_error_free(mem, "Substr: error malloc occured");
	init_string(&string, dst, TRUE, mem);
	free(dst);
	return (string);
}

void	erase_string(t_string *string, char *to_erase, size_t start,
	t_list **mem)
{
	t_string	temp;

	init_string(&temp, &string->str[start + ft_strlen(to_erase)], TRUE, mem);
	dup_string(string, temp.str, start, mem);
}

void	add_string(t_string *string, char *to_add, size_t index, t_list **mem)
{
	t_string	before;
	t_string	after;

	if (!to_add)
		return ;
	before = sub_string(string->str, 0, index, mem);
	after = sub_string(string->str, index, string->size - 1 - index, mem);
	init_string(string, before.str, TRUE, mem);
	dup_string(string, to_add, string->size - 1, mem);
	dup_string(string, after.str, string->size - 1, mem);
}

char	**strings_to_array(t_string *strings, t_list **mem)
{
	int		i;
	char	**dst;

	i = 0;
	while (strings[i].str)
		i++;
	dst = ft_malloc(mem, sizeof(char *) * (i + 1));
	i = 0;
	while (strings[i].str)
	{
		dst[i] = strings[i].str;
		i++;
	}
	dst[i] = 0;
	return (dst);
}

t_string	join_string(char *s1, char *s2, t_list **mem)
{
	t_string	string;

	string.str = 0;
	if (!s1 && !s2)
		return (string);
	if (!s1)
		return (sub_string(s2, 0, ft_strlen(s2), mem));
	if (!s2)
		return (sub_string(s1, 0, ft_strlen(s2), mem));
	init_string(&string, s1, TRUE, mem);
	add_string(&string, s2, string.size - 1, mem);
	return (string);
}
