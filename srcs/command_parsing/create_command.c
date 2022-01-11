/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:47:50 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/11 13:31:37 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_command(t_command *command)
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

t_bool	is_arg(char *arg)
{
	if (arg[0] == '$' && arg[1] != '\'')
		return (TRUE);
	else if (arg[0] == '\"' && arg[1] == '$' && arg[2] != '\'')
		return (TRUE);
	return (FALSE);
}

void	find_arg_and_replace(t_string *arg, t_string *command, int start,
	t_lst_env *export)
{
	int			end;
	t_string	temp;

	end = start + 1;
	while (command->str[end] != ' ' && command->str[end] != '\''
		&& command->str[end] != '\"' && command->str[end] != '$'
		&& command->str[end])
		end++;
	sub_string(arg, command->str, start + 1, end - (start + 1));
	temp = lst_env_find_name_var(export, arg->str);
	// add_string(arg, "$", 0);
	if (temp.str)
		replace_string(command, start - 1, temp.str, temp.size - 1);
	else
		erase_string(command, arg->str, start - 1);
}

int	check_arg(t_command *command, t_head_env *envi)
{
	int			start;
	t_string	arg;

	start = 1;
	init_string(&arg, "", TRUE);
	if (is_arg(command->command.str))
		find_arg_and_replace(&arg, &command->command, start - 1, envi->export);
	while (command->command.str[start])
	{
		if (is_arg(&command->command.str[start]))
			find_arg_and_replace(&arg, &command->command, start - 1,
				envi->export);
		start++;
	}
	reinit_string(&arg);
	return (0);
}

int	create_command(t_command *command, t_head_env *envi)
{
	if (!command->command.str)
		exit(-1);
	if (!check_command(command))
		return (0);
	check_arg(command, envi);
	split_wog(command, ' ');
	return (1);
}
