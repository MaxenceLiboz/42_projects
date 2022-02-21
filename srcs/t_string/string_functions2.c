/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_functions2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:34:57 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/21 10:44:39 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Use ft_substr and convert it to a string
*/
t_string	sub_string(char *src, size_t start, size_t size, t_prg *prg)
{
	t_string	string;
	char		*dst;

	dst = ft_substr(src, start, size);
	if (!dst)
		ft_error_exit(prg, 1, "substr: error malloc occured");
	init_string(&string, dst, TRUE, prg);
	free(dst);
	return (string);
}

/*
	Erase a char * from a string
*/
void	erase_string(t_string *string, char *to_erase, size_t start,
	t_prg *prg)
{
	t_string	temp;

	init_string(&temp, &string->str[start + ft_strlen(to_erase)], TRUE, prg);
	dup_string(string, temp.str, start, prg);
}

/*
	Add something anywhere to a string
*/
void	add_string(t_string *string, char *to_add, size_t index, t_prg *prg)
{
	t_string	before;
	t_string	after;

	if (!to_add)
		return ;
	before = sub_string(string->str, 0, index, prg);
	after = sub_string(string->str, index, string->size - 1 - index, prg);
	init_string(string, before.str, TRUE, prg);
	dup_string(string, to_add, string->size - 1, prg);
	dup_string(string, after.str, string->size - 1, prg);
}

/*
	Convert a string* to a char **
*/
char	**strings_to_array(t_string *strings, t_prg *prg)
{
	int		i;
	char	**dst;

	i = 0;
	while (strings[i].str)
		i++;
	dst = ft_malloc(prg, sizeof(char *) * (i + 1));
	i = 0;
	while (strings[i].str)
	{
		dst[i] = strings[i].str;
		i++;
	}
	dst[i] = 0;
	return (dst);
}

/*
	Join two string together
*/
t_string	join_string(char *s1, char *s2, t_prg *prg)
{
	t_string	string;

	string.str = 0;
	if (!s1 && !s2)
		return (string);
	if (!s1)
		return (sub_string(s2, 0, ft_strlen(s2), prg));
	if (!s2)
		return (sub_string(s1, 0, ft_strlen(s2), prg));
	init_string(&string, s1, TRUE, prg);
	add_string(&string, s2, string.size - 1, prg);
	return (string);
}
