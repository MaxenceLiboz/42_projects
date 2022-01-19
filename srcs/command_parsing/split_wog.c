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

	if (dquotes > 0 || squotes > 0)
	{
		while (src[*i] == c)
			*i += 1;
	}
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

static void	ft_copy2(t_command *command, int *i, int end, int dsti)
{
	int		dquotes;
	int		squotes;
	int		y;

	dquotes = 1;
	squotes = 1;
	y = 0;
	while (*i < end)
	{
		while (command->command.str[*i] == '"' && squotes == 1)
		{
			*i += 1;
			dquotes *= -1;
		}
		while (command->command.str[*i] == '\'' && dquotes == 1)
		{
			*i += 1;
			squotes *= -1;
		}
		if (*i >= end)
			break ;
		command->array[dsti].str[y++] = command->command.str[*i];
		*i += 1;
	}
	command->array[dsti].str[y] = 0;
	*i = end;
}

static void	ft_copy(t_prg *prg, char c, int *i, int dsti)
{
	int			end;
	int			size;

	get_copy_size(prg->cmd.command.str, c, i, &end);
	size = end - *i;
	prg->cmd.array[dsti].str = ft_malloc(&prg->mem, sizeof(char) * (size + 1));
	if (!prg->cmd.array[dsti].str)
		exit(-1);
	ft_copy2(&prg->cmd, i, end, dsti);
	init_string(&prg->cmd.command, prg->cmd.command.str, FALSE, &prg->mem);
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
