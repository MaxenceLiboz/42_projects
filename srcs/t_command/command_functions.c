/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 11:37:42 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/12 17:10:21 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_command(t_command *array_string, int size, int to_malloc)
{
	array_string->size = size;
	array_string->max_size = size;
	if (to_malloc != TRUE)
		return ;
	array_string->array = malloc(sizeof(t_string) * size);
	if (!array_string->array)
		exit(-1);
}

void	reinit_command(t_command *cmd)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	reinit_string(&cmd->command);
	if (cmd->size == 0)
		return ;
	while (y < cmd->max_size)
		reinit_string(&cmd->array[y++]);
	free(cmd->array);
	cmd->max_size = 0;
	cmd->index = 0;
	cmd->size = 0;
}

char	**get_cmd(t_command *cmd)
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
	dst = malloc(sizeof(char *) * ((end - cmd->index) + 1));
	if (!dst)
		exit(-1);
	while (cmd->index < end)
	{
		if (*cmd->array[cmd->index].str)
			dst[i++] = ft_strdup(cmd->array[cmd->index].str);
		cmd->index += 1;
	}
	dst[i] = 0;
	return (dst);
}

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
