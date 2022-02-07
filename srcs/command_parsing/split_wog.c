/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_wog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:30:47 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/07 11:35:54 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	get_copy_size(const char *src, char c, int *i, int *end)
{
	static int	dquotes = 1;
	static int	squotes = 1;

	while (src[*i] == c)
			*i += 1;
	*end = *i;
	while ((src[*end] != c || dquotes < 1 || squotes < 1)
		&& src[*end] && src[*end])
	{
		if (src[*end] == '"' && squotes == 1)
			dquotes *= -1;
		if (src[*end] == '\'' && dquotes == 1)
			squotes *= -1;
		*end += 1;
	}
}

static void	ft_copy(t_prg *prg, char c, int *i, int dsti)
{
	int			end;
	int			size;

	get_copy_size(prg->cmd.command.str, c, i, &end);
	size = end - *i;
	prg->cmd.array[dsti] = sub_string(prg->cmd.command.str,
			*i, size, &prg->mem);
	*i = end;
}

void	split_wog(t_prg *prg, char c)
{
	int		words;
	int		i;
	int		dsti;

	i = 0;
	dsti = 0;
	words = count_split_wog(prg->cmd.command.str, c);
	init_command(&prg->cmd, words, TRUE, &prg->mem);
	while (words--)
	{
		ft_copy(prg, c, &i, dsti);
		dsti++;
	}
}
