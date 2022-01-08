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
		if (src[*end] == '"')
			dquotes *= -1;
		if (src[*end] == '\'')
			squotes *= -1;
		*end += 1;
	}
}

static void	ft_copy(t_array_string *command, char c, int *i, int dsti)
{
	int			end;
	int			size;
	int			y;

	y = 0;
	get_copy_size(command->command.str, c, i, &end);
	size = end - *i;
	command->array[dsti].str = malloc(sizeof(char) * (size + 1));
	while (*i < end)
	{
		if (command->command.str[*i] == '"')
			*i += 1;
		if (command->command.str[*i] == '\'')
			*i += 1;
		if (*i >= end)
			break ;
		command->array[dsti].str[y++] = command->command.str[*i];
		*i += 1;
	}
	command->array[dsti].str[y] = 0;
	init_string(&command->command, command->command.str, FALSE);
	*i = end;
}

void	split_wog(t_array_string *command, char c)
{
	int		words;
	int		i;
	int		dsti;

	i = 0;
	dsti = 0;
	words = count_split_wog(command->command.str, c);
	init_array_string(command, words, TRUE);
	while (words--)
	{
		ft_copy(command, c, &i, dsti);
		dsti++;
	}
}
