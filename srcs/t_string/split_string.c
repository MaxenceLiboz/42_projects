/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:44:10 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/17 13:43:20 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Count the number of words to split
*/
static int	ft_count_words(const char *str, char charset)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] && str[i] == charset)
		i++;
	if (str[i] != 0)
		count++;
	while (str[i])
	{
		if (str[i] == charset
			&& (str[i + 1] != charset && str[i + 1] != 0))
			count++;
		i++;
	}
	return (count);
}

static t_string	ft_copy(char *src, char c, int *i, t_prg *prg)
{
	int			end;
	t_string	dst;
	int			size;

	while (src[*i] == c)
		*i += 1;
	end = *i;
	while (src[end] != c && src[end])
		end++;
	size = end - *i;
	dst = sub_string(src, *i, size, prg);
	*i = end;
	return (dst);
}

/*
	Split a string in a string *
*/
t_string	*split_string(char *s, char c, t_prg *prg)
{
	t_string	*dst;
	int			words;
	int			i;
	int			dsti;

	if (!s)
		return (0);
	i = 0;
	dsti = 0;
	words = ft_count_words(s, c);
	dst = ft_malloc(prg, sizeof(t_string) * (words + 1));
	while (words--)
	{
		dst[dsti] = ft_copy(s, c, &i, prg);
		dsti++;
	}
	dst[dsti].str = 0;
	return (dst);
}
