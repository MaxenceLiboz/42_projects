/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:18:56 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/09 17:47:17 by mliboz           ###   ########.fr       */
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



// /*
// 	Get the whole argument returned as a string;
// */
// t_string	get_full_arg(t_string *str, int start, t_list **mem)
// {
// 	int			end;
// 	t_string	dst;

// 	end = start + 1;
// 	if (str->str[end] == "{")
// 		end++;
// 	while (ft_isalnum(str->str[end]))
// 		end++;
// 	if (str->str[end] == "}")
// 		end++;
// 	return (dst = sub_string(str->str, start, end - start, mem));
// }

// /*
// 	Get only the argument => should be the same as the one in our list
// */
// t_string	get_arg(t_string arg, t_list **mem)
// {
// 	int			start;
// 	int			end;
// 	t_string	dst;

// 	start = 0;
// 	while (ft_isalnum(arg.str[start] == 1))
// 		start++;
// 	end = start;
// 	while (ft_isalnum(arg.str[end]))
// 		end++;
// 	return (dst = sub_string(arg.str, start, end - start, mem));
// }

// void	find_arg_and_replace(t_prg *prg, int start, t_string *str)
// {
// 	t_string	full_arg;
// 	t_string	arg;
// 	int			indexs[2];

// 	full_arg = get_full_arg(str, start, &prg->mem);
// 	arg = get_arg(full_arg, &prg->mem);
// 	dup_string(&arg, lst_env_find_name_var(prg->env.export, arg.str).str,
// 		0, &prg->mem);
// 	indexs[0] = start;
// 	indexs[1] = full_arg.size;
// 	if (arg.str)
// 		replace_string(str, indexs, arg.str, &prg->mem);
// 	else
// 		erase_string(str, full_arg.str, start, &prg->mem);
// }

// /*
// 	Remove $ sign if next to ' or "
// */
// void	remove_dolard_if_needed(t_string *str, int index, t_list **mem)
// {
// 	if (str->str[index] == '$' && str->str[index + 1]
// 		&& (str->str[index + 1] == '\'' || str->str[index + 1] == '\"'))
// 		erase_string(str, "$", index, mem);
// }

// /*
// 	Check if it is an arg and return TRUE or FALSE
// */
// t_bool	is_arg(char *arg, int *index)
// {
// 	if (arg[*index] == '$')
// 	{
// 		if (ft_isalnum(arg[*index + 1]) || arg[*index + 1] == '?')
// 			return (TRUE);
// 		else if (arg[*index + 1] == '{' )
// 		{
// 			*index += 1;
// 			return (TRUE);
// 		}
// 	}
// 	return (FALSE);
// }

// /*
// 	Find envp varaible and replace it by its value
// */
// void	change_arg_command(t_prg *prg, t_string *str)
// {
// 	int			index;
// 	int			dquotes;

// 	index = 0;
// 	dquotes = -1;
// 	if (is_arg(str->str, &index) == TRUE)
// 		find_arg_and_replace(prg, index, str);
// 	index++;
// 	while (str->str[index])
// 	{
// 		if (str->str[index] == '\"')
// 			dquotes *= -1;
// 		if (str->str[index] == '\'' && dquotes > 1)
// 		{
// 			while (str->str[++index] != '\'')
// 				;
// 			index++;
// 		}
// 		if (is_arg(str->str, &index) == TRUE)
// 			find_arg_and_replace(prg, index, str);
// 		remove_dolard_if_needed(str, index, &prg->mem);
// 		index++;
// 	}
// }
