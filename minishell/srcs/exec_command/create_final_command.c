/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_final_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:31:41 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/17 10:23:55 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	create_final_command_size(char **cmd)
{
	int			i;
	int			y;

	i = 0;
	y = 0;
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], ">", 2) == 0 || ft_strncmp(cmd[i], "<", 2) == 0
			|| ft_strncmp(cmd[i], ">>", 2) == 0
			|| ft_strncmp(cmd[i], "<<", 2) == 0)
			i += 2;
		else
			i++;
		y++;
	}
	return (y);
}

char	**create_final_command(char **cmd, t_prg *prg)
{
	int			i;
	int			y;
	int			size;
	t_string	*strings;

	i = 0;
	y = 0;
	size = sizeof(t_string) * (create_final_command_size(cmd) + 1);
	strings = ft_malloc(prg, size);
	while (cmd[i] != NULL)
	{
		if ((ft_strncmp(cmd[i], ">", 2) == 0 || ft_strncmp(cmd[i], "<", 2) == 0
				|| ft_strncmp(cmd[i], ">>", 2) == 0
				|| ft_strncmp(cmd[i], "<<", 2) == 0) && cmd[i + 1])
			i += 2;
		else
			init_string(&strings[y++], cmd[i++], TRUE, prg);
	}
	strings[y].str = 0;
	return (strings_to_array(strings, prg));
}
