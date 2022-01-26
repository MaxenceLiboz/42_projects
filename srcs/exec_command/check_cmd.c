/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:57:38 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/26 11:22:22 by tarchimb         ###   ########.fr       */
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
		i++;
		y++;
	}
	return (y);
}

static char	**f_cmd(char **cmd, t_list **mem)
{
	int			i;
	int			y;
	t_string	*strings;

	i = 0;
	y = 0;
	strings = ft_malloc(mem, sizeof(t_string) * (f_cmd_size(cmd) + 1));
	while (cmd[i])
	{
		if (ft_strncmp(cmd[i], ">", 2) == 0 || ft_strncmp(cmd[i], "<", 2) == 0
			|| ft_strncmp(cmd[i], ">>", 2) == 0
			|| ft_strncmp(cmd[i], "<<", 2) == 0)
			i += 2;
		else
			init_string(&strings[y++], cmd[i++], TRUE, mem);
	}
	strings[y].str = 0;
	return (strings_to_array(strings, mem));
}

int	ft_open(char *file, char *options)
{
	int		fd;

	fd = -1;
	if (ft_strncmp(options, "CRA", 4) == 0)
		fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (ft_strncmp(options, "CRT", 4) == 0)
		fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (ft_strncmp(options, "R_OK", 5) == 0)
	{
		if (access(file, R_OK) == 0)
			fd = open(file, O_RDONLY);
		else
			return (print_stderror(-1, "open", strerror(errno)));
	}
	if (fd == -1)
		return (print_stderror(-1, "open", strerror(errno)));
	return (fd);
}

int	check_cmd(t_prg *prg, t_lst_cmd *cmd)
{
	int		i;

	i = 0;
	prg->fd.fd_in = 0;
	prg->fd.fd_out = 0;
	while (cmd->cmd[i])
	{
		if (ft_strncmp(cmd->cmd[i], "<", 2) == 0)
			prg->fd.fd_in = ft_open(cmd->cmd[i + 1], "R_OK");
		if (ft_strncmp(cmd->cmd[i], ">", 2) == 0)
			prg->fd.fd_out = ft_open(cmd->cmd[i + 1], "CRT");
		if (ft_strncmp(cmd->cmd[i], ">>", 3) == 0)
			prg->fd.fd_out = ft_open(cmd->cmd[i + 1], "CRA");
		i++;
	}
	cmd->cmd = f_cmd(cmd->cmd, &prg->mem);
	if (prg->fd.fd_in == -1 || prg->fd.fd_out == -1)
		return (-1);
	return (0);
}
