/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:44:10 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/05 11:20:40 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static t_string	ft_copy(char *src, char c, int *i, t_list **mem)
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
	dst = sub_string(src, *i, size, mem);
	*i = end;
	return (dst);
}

t_string	*split_string(char *s, char c, t_list **mem)
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
	dst = ft_malloc(mem, sizeof(t_string) * (words + 1));
	while (words--)
	{
		dst[dsti] = ft_copy(s, c, &i, mem);
		dsti++;
	}
	dst[dsti].str = 0;
	return (dst);
}
