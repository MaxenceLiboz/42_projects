/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:40:44 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/16 10:45:22 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Reporducing export command in bash
*/
int	ft_export(t_head_env *head, char **command, t_list **mem)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!command[i + 1])
		return (print_export(head));
	while (command[++i])
	{
		var_name = sub_string(command[i], 0, ft_strchr_len(command[i], '='),
				mem).str;
		if (control_args(var_name) == SUCCESS)
		{
			if (lst_env_find_name_var(head->export, var_name).str == 0)
				add_elem_to_lst(command[i], head, mem);
			else
				if (ft_strchr(command[i], '=') != 0)
					replace_elem_of_lst(head, command[i], var_name, mem);
		}
		else
			print_stderror(1, 3, "export: `", command[i],
				"': not a valid identifier");
	}
	return (0);
}
