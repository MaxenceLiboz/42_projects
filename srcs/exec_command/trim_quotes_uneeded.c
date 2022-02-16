/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_uneeded.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 10:36:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/16 11:53:44 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	get_size_to_dup(const char *src)
{
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while (src[i])
	{
		if (src[i] == '\"')
		{
			quotes += 2;
			while (src[++i] && src[i] != '\"')
				;
		}
		if (src[i] == '\'')
		{
			quotes += 2;
			while (src[++i] && src[i] != '\'')
				;
		}
		i++;
	}
	return (i - quotes);
}

static char	*ft_strdup_and_trim(const char *src, t_list **mem)
{
	int		i;
	int		j;
	char	*dest;

	j = 0;
	dest = ft_malloc(mem, sizeof(char) * (get_size_to_dup(src) + 1));
	i = 0;
	while (src[i])
	{
		if (src[i] == '\'')
		{
			while (src[i] && src[++i] != '\'')
				dest[j++] = src[i];
			i++;
		}
		else if (src[i] == '\"')
		{
			while (src[i] && src[++i] != '\"')
				dest[j++] = src[i];
			i++;
		}
		else
			dest[j++] = src[i++];
	}
	dest[j] = '\0';
	return (dest);
}

char	**trim_quotes_unneeded(char **cmd, t_list **mem)
{
	char	**dst;
	int		i;

	i = 0;
	while (cmd[i])
		i++;
	dst = ft_malloc(mem, sizeof(char *) * (i + 1));
	i = 0;
	while (cmd[i])
	{
		dst[i] = ft_strdup_and_trim(cmd[i], mem);
		i++;
	}
	dst[i] = 0;
	return (dst);
}