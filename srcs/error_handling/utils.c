/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 10:39:26 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 12:04:19 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_double_dup(int fd1, int fd2, t_prg *prg)
{
	if (fd1 > 0)
	{
		if (dup2(fd1, STDIN_FILENO) == -1)
			ft_error_exit(prg, 1, "STDIN_FILENO dup failed");
	}
	if (fd2 > 0)
	{
		if (dup2(fd2, STDOUT_FILENO) == -1)
			ft_error_exit(prg, 1, "STDOUT_FILENO dup failed");
	}
}

void	ft_pipe(int *fd, t_prg *prg)
{
	if (pipe(fd) == -1)
		ft_error_exit(prg, 2, "pipe: ", strerror(errno));
}

void	ft_close(int fd, t_prg *prg)
{
	if (close(fd) == -1)
		ft_error_exit(prg, 2, "close: ", strerror(errno));
}

void	ft_dup2(int fd1, int fd2, t_prg *prg)
{
	if (dup2(fd1, fd2) == -1)
		ft_error_exit(prg, 2, "dup2: ", strerror(errno));
}

void	ft_open(char *file, char *options, int *fd, t_prg *prg)
{
	file = ft_strdup_and_trim(file, 0, prg);
	if (!file)
		return ;
	if (*fd > 0 && *fd != prg->fd.stdin_save && *fd != prg->fd.stdout_save)
		ft_close(*fd, prg);
	if (ft_strncmp(options, "CRA", 4) == 0)
		*fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (ft_strncmp(options, "CRT", 4) == 0)
		*fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (ft_strncmp(options, "ROK", 4) == 0)
	{
		if (access(file, R_OK) == 0)
			*fd = open(file, O_RDONLY);
		else
			ft_error_exit(prg, 2, "access: ", strerror(errno));
	}
	if (*fd == -1)
		ft_error_exit(prg, 2, "open: ", strerror(errno));
}
