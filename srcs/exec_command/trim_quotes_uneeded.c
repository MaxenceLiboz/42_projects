/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_uneeded.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 10:36:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 12:01:49 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pass_quotes(char *src, int *i, int *quotes, char c)
{
	*i += 1;
	while (src[*i] && src[*i] != c)
		*i += 1;
	*i += 1;
	*quotes += 2;
}

/*
	Get the good size for the ft_strdup_and_trim();
*/
static int	get_size_to_dup(char *src)
{
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	if (!src)
		return (0);
	while (src[i])
	{
		if (src[i] == '\"')
			pass_quotes(src, &i, &quotes, '\"');
		else if (src[i] == '\'')
			pass_quotes(src, &i, &quotes, '\'');
		else
			i++;
	}
	return (i - quotes);
}

/*
	Dup a string and trim the quotes
*/
char	*ft_strdup_and_trim(char *src, int j, t_prg *prg)
{
	int		i;
	char	*dest;

	if (!src)
		return (NULL);
	dest = ft_malloc(prg, sizeof(char) * (get_size_to_dup(src) + 1));
	i = 0;
	while (src[i])
	{
		if (src[i] == '\'')
			while (src[++i] && src[i] != '\'')
				dest[j++] = src[i];
		else if (src[i] == '\"')
			while (src[++i] && src[i] != '\"')
				dest[j++] = src[i];
		else
			dest[j++] = src[i];
		i++;
	}
	dest[j] = '\0';
	return (dest);
}

/*
	Trim the quotes to create the final command to send to execve or exec_builtins
*/
char	**trim_quotes_unneeded(char **cmd, t_prg *prg)
{
	char	**dst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
		i++;
	dst = ft_malloc(prg, sizeof(char *) * (i + 1));
	i = 0;
	while (cmd[i])
	{
		dst[i] = ft_strdup_and_trim(cmd[i], j, prg);
		i++;
	}
	dst[i] = 0;
	return (dst);
}
