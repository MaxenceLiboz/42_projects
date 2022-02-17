/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 10:39:26 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 09:32:24 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_double_dup(int fd1, int fd2, t_list **mem)
{
	if (fd1 > 0)
	{
		if (dup2(fd1, STDIN_FILENO) == -1)
			ft_error_exit(mem, 1, "STDIN_FILENO dup failed");
	}
	if (fd2 > 0)
	{
		if (dup2(fd2, STDOUT_FILENO) == -1)
			ft_error_exit(mem, 1, "STDOUT_FILENO dup failed");
	}
}

void	ft_pipe(int *fd, t_list **mem)
{
	if (pipe(fd) == -1)
		ft_error_exit(mem, 2, "pipe: ", strerror(errno));
}

void	ft_write(int fd, char *str, size_t size, t_list **mem)
{
	if (write(fd, str, size) == -1)
		ft_error_exit(mem, 2, "write: ", strerror(errno));
}

void	ft_close(int fd, t_list **mem)
{
	if (close(fd) == -1)
		ft_error_exit(mem, 2, "close: ", strerror(errno));
}

void	ft_open(char *file, char *options, int *fd, t_prg *prg)
{
	file = ft_strdup_and_trim(file, 0, &prg->mem);
	if (!file)
		return ;
	if (*fd > 0 && *fd != prg->fd.stdin_save && *fd != prg->fd.stdout_save)
		ft_close(*fd, &prg->mem);
	if (ft_strncmp(options, "CRA", 4) == 0)
		*fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (ft_strncmp(options, "CRT", 4) == 0)
		*fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (ft_strncmp(options, "ROK", 4) == 0)
	{
		if (access(file, R_OK) == 0)
			*fd = open(file, O_RDONLY);
		else
			ft_error_exit(&prg->mem, 2, "access: ", strerror(errno));
	}
	if (*fd == -1)
		ft_error_exit(&prg->mem, 2, "open: ", strerror(errno));
}
