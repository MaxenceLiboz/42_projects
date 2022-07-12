/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:18:56 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/21 10:38:11 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Get the whole argument returned as a string;
*/
t_string	get_full_arg(t_string *str, int start, t_prg *prg)
{
	int			end;
	t_string	dst;

	end = start + 1;
	if (end - 1 == start && str->str[end] == '?')
		return (dst = sub_string(str->str, start, end + 1 - start, prg));
	while (ft_isalnum(str->str[end]))
		end++;
	dst = sub_string(str->str, start, end - start, prg);
	return (dst);
}

/*
	Get only the argument => should be the same as the one in our list
*/
t_string	get_arg(t_string arg, t_prg *prg)
{
	int			start;
	int			end;
	t_string	dst;

	start = 1;
	end = start;
	while (ft_isalnum(arg.str[end]))
		end++;
	return (dst = sub_string(arg.str, start, end - start, prg));
}

/*
	get_full_arg;
	get_arg;
	arg = ? => replace full_arg by exit_status;
	arg find => replace full_arg by envp
	arg not find => erase full_arg
	arg starting by number => erase $ and first digit
*/
void	find_arg_and_replace(t_prg *prg, int start, t_string *str)
{
	t_string	full_arg;
	t_string	arg;
	int			indexs[2];
	t_string	exit_status;
	char		*value;

	value = ft_itoa(g_returnvalue);
	init_string(&exit_status, value, TRUE, prg);
	free(value);
	full_arg = get_full_arg(str, start, prg);
	arg = get_arg(full_arg, prg);
	indexs[0] = start;
	indexs[1] = full_arg.size - 1;
	dup_string(&arg, lst_env_find_name_var(prg->env.export, arg.str).str,
		0, prg);
	if (full_arg.str[1] == '?')
		replace_string(str, indexs, exit_status.str, prg);
	else if (ft_isdigit(full_arg.str[1]) == TRUE)
		erase_string(str, "$n", start, prg);
	else if (arg.str)
		replace_string(str, indexs, arg.str, prg);
	else
		erase_string(str, full_arg.str, start, prg);
}

/*
	Check if it is an arg and return TRUE or FALSE
*/
t_bool	is_arg(char *arg, int *index)
{
	if (arg[*index] && arg[*index] == '$')
	{
		if (ft_isalnum(arg[*index + 1]) || arg[*index + 1] == '?')
			return (TRUE);
	}
	return (FALSE);
}

/*
	Find envp varaible or $? and replace it by its value
*/
void	change_arg_command(t_prg *prg, t_string *str)
{
	int			i;
	int			dquotes;

	i = 0;
	dquotes = -1;
	while (str->str[i])
	{
		if (str->str[i] == '\"')
			dquotes *= -1;
		if (str->str[i] == '\'' && dquotes < 1)
			pass_quotes(str->str, &i, '\'');
		if (str->str[i] && str->str[i] != '\0')
		{
			if (is_arg(str->str, &i) == TRUE)
				find_arg_and_replace(prg, i, str);
			if (dquotes < 1 && str->str[i] == '$' && str->str[i + 1]
				&& (str->str[i + 1] == '\'' || str->str[i + 1] == '\"'))
				erase_string(str, "$", i, prg);
			else
				i++;
		}
	}
}
