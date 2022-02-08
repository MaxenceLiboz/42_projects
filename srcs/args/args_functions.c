/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:18:56 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/08 10:51:33 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_arg(char *arg, int *start)
{
	// printf("%s, %c, %c, %d\n", &arg[*start], arg[*start], arg[*start + 1], ft_isalnum(arg[*start + 1]) || arg[*start + 1] == '?');
	if (arg[*start] == '$'
		&& (ft_isalnum(arg[*start + 1]) || arg[*start + 1] == '?'))
		return (TRUE);
	else if (arg[*start] == '\"' && arg[*start + 1] == '$'
		&& (ft_isalnum(arg[*start + 2]) || arg[*start + 2] == '?'))
	{
		*start += 1;
		return (TRUE);
	}
	return (FALSE);
}

static void	next_arg(char *arg, int *start)
{
	if (arg[*start] == '<' || arg[*start] == '>')
	{
		while (arg[*start] != ' ' && arg[*start])
			*start += 1;
		while (arg[*start] == ' ' && arg[*start])
			*start += 1;
		while (arg[*start] != ' ' && arg[*start])
			*start += 1;
	}
}

void	find_arg_and_replace(t_prg *prg, t_string *arg, int start,
	t_string *str)
{
	int			end;
	t_string	tmp;
	int			indexs[2];

	end = start + 1;
	if (str->str[start + 1] == '?')
	{
		init_string(arg, ft_itoa(prg->return_value), TRUE, &prg->mem);
		indexs[0] = start;
		indexs[1] = arg->size;
		replace_string(str, indexs, arg->str, &prg->mem);
		return ;
	}
	while (ft_isalnum(str->str[end]))
		end++;
	*arg = sub_string(str->str, start + 1, end - (start + 1),
			&prg->mem);
	tmp = lst_env_find_name_var(prg->env.export, arg->str);
	indexs[0] = start;
	indexs[1] = arg->size;
	if (tmp.str)
		replace_string(str, indexs, tmp.str, &prg->mem);
	else
		erase_string(str, arg->str, start, &prg->mem);
}

void	change_arg_command(t_prg *prg, t_string *str)
{
	int			start;
	t_string	arg;
	int			squotes;
	int			dquotes;

	start = 0;
	dquotes = -1;
	squotes = -1;
	init_string(&arg, "", TRUE, &prg->mem);
	if (is_arg(str->str, &start))
		find_arg_and_replace(prg, &arg, start, str);
	start++;
	while (str->str[start])
	{
		if (str->str[start] == '\"' && squotes < 1)
			dquotes *= -1;
		if (str->str[start] == '\'' && dquotes < 1)
			squotes *= -1;
		if (squotes < 1 && dquotes < 1)
			next_arg(str->str, &start);
		if (is_arg(str->str, &start))
			find_arg_and_replace(prg, &arg, start, str);
		start++;
	}
}
