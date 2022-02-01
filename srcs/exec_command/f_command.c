/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_command.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 14:31:41 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/01 14:47:25 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	f_cmd_size(char **cmd)
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

char	**f_cmd(char **cmd, t_list **mem)
{
	int			i;
	int			y;
	int			size;
	t_string	*strings;

	i = 0;
	y = 0;
	size = sizeof(t_string) * (f_cmd_size(cmd) + 1);
	strings = ft_malloc(mem, size);
	while (cmd[i] != NULL)
	{
		if ((ft_strncmp(cmd[i], ">", 2) == 0 || ft_strncmp(cmd[i], "<", 2) == 0
				|| ft_strncmp(cmd[i], ">>", 2) == 0
				|| ft_strncmp(cmd[i], "<<", 2) == 0) && cmd[i + 1])
			i += 2;
		else
			init_string(&strings[y++], cmd[i++], TRUE, mem);
	}
	strings[y].str = 0;
	return (strings_to_array(strings, mem));
}
