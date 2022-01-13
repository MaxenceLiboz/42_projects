/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:47:50 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/13 14:30:22 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_bool	is_arg(char *arg, int *start)
{
	if (arg[*start] == '$'
		&& ft_isalnum(arg[*start + 1]))
		return (TRUE);
	else if (arg[*start] == '\"' && arg[*start + 1] == '$'
		&& ft_isalnum(arg[*start + 2]))
	{
		*start += 1;
		return (TRUE);
	}
	return (FALSE);
}

static void	find_arg_and_replace(t_string *arg, t_string *command, int start,
	t_lst_env *export)
{
	int			end;
	t_string	temp;

	end = start + 1;
	while (ft_isalnum(command->str[end]))
		end++;
	sub_string(arg, command->str, start + 1, end - (start + 1));
	temp = lst_env_find_name_var(export, arg->str);
	add_string(arg, "$", 0);
	if (temp.str)
		replace_string(command, start, temp.str, arg->size - 1);
	else
		erase_string(command, arg->str, start);
}

static void	change_arg_command(t_command *command, t_head_env *envi)
{
	int			start;
	t_string	arg;

	start = 0;
	init_string(&arg, "", TRUE);
	if (is_arg(command->command.str, &start))
		find_arg_and_replace(&arg, &command->command, start, envi->export);
	start++;
	while (command->command.str[start])
	{
		if (is_arg(command->command.str, &start))
			find_arg_and_replace(&arg, &command->command, start,
				envi->export);
		start++;
	}
	reinit_string(&arg);
}

t_lst_cmd	*create_command(t_command *command, t_head_env *envi)
{
	t_lst_cmd	*lst;

	lst = 0;
	command->size = 0;
	if (!check_quotes(command->command)
		|| count_split_wog(command->command.str, ' ') == 0)
		return (0);
	change_arg_command(command, envi);
	split_wog(command, ' ');
	// if (!check_pipes(*command))
	// 	return (0);
	lst = lst_cmd_init(command);
	return (lst);
}
