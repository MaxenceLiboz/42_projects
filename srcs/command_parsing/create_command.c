/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:47:50 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/19 14:00:33 by maxencelibo      ###   ########.fr       */
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

static void	find_arg_and_replace(t_prg *prg, t_string *arg, int start)
{
	int			end;
	t_string	temp;
	int			indexs[2];

	end = start + 1;
	while (ft_isalnum(prg->cmd.command.str[end]))
		end++;
	*arg = sub_string(prg->cmd.command.str, start + 1, end - (start + 1),
			&prg->mem);
	temp = lst_env_find_name_var(prg->env.export, arg->str);
	add_string(arg, "$", 0, &prg->mem);
	indexs[0] = start;
	indexs[1] = arg->size - 1;
	if (temp.str)
		replace_string(&prg->cmd.command, indexs, temp.str, &prg->mem);
	else
		erase_string(&prg->cmd.command, arg->str, start, &prg->mem);
}

static void	change_arg_command(t_prg *prg)
{
	int			start;
	t_string	arg;

	start = 0;
	init_string(&arg, "", TRUE, &prg->mem);
	if (is_arg(prg->cmd.command.str, &start))
		find_arg_and_replace(prg, &arg, start);
	start++;
	while (prg->cmd.command.str[start])
	{
		if (is_arg(prg->cmd.command.str, &start))
			find_arg_and_replace(prg, &arg, start);
		start++;
	}
}

t_lst_cmd	*create_command(t_prg *prg)
{
	t_lst_cmd	*lst;

	lst = 0;
	prg->cmd.command.size = 0;
	if (!check_quotes(prg->cmd.command)
		|| count_split_wog(prg->cmd.command.str, ' ') == 0)
		return (0);
	change_arg_command(prg);
	split_wog(prg, ' ');
	if (!check_pipes(prg->cmd))
		return (0);
	lst = lst_cmd_init(&prg->cmd, &prg->mem);
	return (lst);
}
