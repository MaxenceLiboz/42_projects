/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:47:50 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/08 11:25:29 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_command(t_array_string *command)
{
	int		squotes;
	int		dquotes;
	int		i;

	squotes = 0;
	dquotes = 0;
	i = 0;
	while (command->command.str[i])
	{
		if (command->command.str[i] == '\"')
			dquotes += 1;
		if (command->command.str[i] == '\'')
			squotes += 1;
		i++;
	}
	if (squotes % 2 != 0 && dquotes % 2 != 0)
		printf("Missing both: \" and \'\n");
	else if (squotes % 2 != 0)
		printf("Missing: \'\n");
	else if (dquotes % 2 != 0)
		printf("Missing: \"\n");
	if (squotes % 2 != 0 || dquotes % 2 != 0)
		return (0);
	return (1);
}

void	free_string(t_string *string)
{
	int		i;

	i = 0;
	if (!string->str)
		return ;
	while (string->str[i])
		string->str[i++] = 0;
	free(string->str);
	string->str = 0;
	string->max_size = 0;
	string->size = 0;
}

void	realloc_string(t_string *string)
{
	t_string	dst;

	init_string(&dst, string->size, TRUE);
	add_string_str(&dst, string->str, 0);
	dst.max_size = string->max_size;
	free_string(string);
	init_string(string, dst.max_size * 2, TRUE);
	add_string_str(string, dst.str, 0);
	free_string(&dst);
}

void	add_string_str(t_string *string, char *src, int index)
{
	int		i;

	i = 0;
	if (!string->str)
		init_string(string, ft_strlen(src), TRUE);
	while (string->max_size < ((string->size) + ft_strlen(src)))
		realloc_string(string);
	while (src[i])
		string->str[index++] = src[i++];
	string->str[index] = 0;
	string->size = ft_strlen(string->str) + 1;
}

void	replace_string(t_string *string, int index, char *replace_with,
			int rsize)
{
	t_string	save;

	init_string(&save, 0, FALSE);
	add_string_str(&save, &string->str[rsize + index], 0);
	add_string_str(string, replace_with, index);
	add_string_str(string, save.str, index + ft_strlen(replace_with));
	free_string(&save);
}

// int	check_arg(t_array_string *command)
// {
// 	int		i;

// 	i = 1;
// 	if (command->command.str[0] == '$' && )
// }

int	create_command(t_array_string *command)
{
	if (!command->command.str)
		exit(-1);
	if (!check_command(command))
		return (0);
	// check_arg(command);
	split_wog(command, ' ');
	return (1);
}
