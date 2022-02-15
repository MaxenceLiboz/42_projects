/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:18:56 by maxencelibo       #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/15 11:10:09 by mliboz           ###   ########.fr       */
=======
/*   Updated: 2022/02/12 15:14:40 by tarchimb         ###   ########.fr       */
>>>>>>> 1cdefa250b332d32a3918d61e242d725082b91d2
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Get the whole argument returned as a string;
*/
t_string	get_full_arg(t_string *str, int start, t_list **mem)
{
	int			end;
	t_string	dst;

	end = start + 1;
	while (ft_isalnum(str->str[end]))
		end++;
	return (dst = sub_string(str->str, start, end - start, mem));
}

/*
	Get only the argument => should be the same as the one in our list
*/
t_string	get_arg(t_string arg, t_list **mem)
{
	int			start;
	int			end;
	t_string	dst;

	start = 1;
	end = start;
	while (ft_isalnum(arg.str[end]))
		end++;
	return (dst = sub_string(arg.str, start, end - start, mem));
}

void	find_arg_and_replace(t_prg *prg, int start, t_string *str)
{
	t_string	full_arg;
	t_string	arg;
	int			indexs[2];

	full_arg = get_full_arg(str, start, &prg->mem);
	arg = get_arg(full_arg, &prg->mem);
	indexs[0] = start;
	indexs[1] = full_arg.size - 1;
	dup_string(&arg, lst_env_find_name_var(prg->env.export, arg.str).str,
		0, &prg->mem);
	if (ft_isdigit(full_arg.str[1]) == TRUE)
		erase_string(str, "$n", start, &prg->mem);
	else if (arg.str)
		replace_string(str, indexs, arg.str, &prg->mem);
	else
		erase_string(str, full_arg.str, start, &prg->mem);
}

/*
	Check if it is an arg and return TRUE or FALSE
*/
t_bool	is_arg(char *arg, int *index)
{
	if (arg[*index] == '$')
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
	int			index;
	int			dquotes;

	index = 0;
	dquotes = -1;
	index++;
	while (str->str[index])
	{
		if (str->str[index] == '\"')
			dquotes *= -1;
		if (str->str[index] == '\'' && dquotes < 1)
		{
			while (str->str[++index] != '\'')
				;
			index++;
		}
		if (is_arg(str->str, &index) == TRUE)
			find_arg_and_replace(prg, index, str);
		if (dquotes < 1 && str->str[index] == '$' && str->str[index + 1]
			&& (str->str[index + 1] == '\'' || str->str[index + 1] == '\"'))
			erase_string(str, "$", index, &prg->mem);
		index++;
	}
}
