/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 10:47:50 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/08 15:26:24 by maxencelibo      ###   ########.fr       */
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
