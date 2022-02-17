/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:37:42 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 13:27:30 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Init our command structure
*/
void	init_command(t_command *array_string, int size, int to_malloc,
			t_prg *prg)
{
	array_string->size = size;
	array_string->max_size = size;
	array_string->index = 0;
	if (to_malloc != TRUE)
		return ;
	array_string->array = ft_malloc(prg, sizeof(t_string) * size);
}

/*
	Reinit the command structure variables
*/
void	reinit_command(t_command *cmd)
{
	cmd->max_size = 0;
	cmd->index = 0;
	cmd->size = 0;
}

/*
	Convert the t_command in char **cmd
*/
char	**get_cmd(t_command *cmd, t_prg *prg)
{
	int		end;
	char	**dst;
	int		i;

	i = 0;
	if (ft_strncmp(cmd->array[cmd->index].str, "|", 2) == 0)
		cmd->index++;
	end = cmd->index;
	while (end < cmd->size
		&& ft_strncmp(cmd->array[end].str, "|", 2) != 0)
		end++;
	dst = ft_malloc(prg, sizeof(char *) * ((end - cmd->index) + 1));
	while (cmd->index < end)
	{
		dst[i] = sub_string(cmd->array[cmd->index].str, 0,
				cmd->array[cmd->index].size - 1, prg).str;
		i++;
		cmd->index += 1;
	}
	dst[i] = 0;
	return (dst);
}

/*
	Get the number of pipes in the command
*/
int	pipes_size_cmd(t_command cmd)
{
	int		i;
	int		pipes;

	i = 0;
	pipes = 0;
	while (cmd.size--)
	{
		if (ft_strncmp(cmd.array[i].str, "|", 2) == 0)
			pipes++;
		i++;
	}
	return (pipes);
}
