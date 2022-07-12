/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:49:02 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/09 14:12:56 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_title(void)
{
	int		fd;
	char	*dest;

	if (access("srcs/custom/title.txt", F_OK | R_OK) == 0)
		fd = open("srcs/custom/title.txt", O_RDONLY);
	else
		return (print_stderror(FAIL, 2, "error: access: ", strerror(errno)));
	if (fd < 0)
		return (print_stderror(FAIL, 2, "error: open: ", strerror(errno)));
	dest = get_next_line(fd);
	while (dest)
	{
		printf("\e[0;32m %s", dest);
		free(dest);
		dest = get_next_line(fd);
	}
	printf("\t\t\t\t\t\t\t\t\t \e[0;37m by tarchimb and mliboz\n");
	if (close(fd) == -1)
		return (print_stderror(FAIL, 2, "error: close: ", strerror(errno)));
	return (SUCCESS);
}

static int	print_biography(char *user)
{
	int		fd;
	char	*dest;

	if (access(user, F_OK | R_OK) == 0)
		fd = open(user, O_RDONLY);
	else
		return (print_stderror(FAIL, 2, "error: access: ", strerror(errno)));
	if (fd < 0)
		return (print_stderror(FAIL, 2, "error: open: ", strerror(errno)));
	dest = get_next_line(fd);
	while (dest)
	{
		printf("%s", dest);
		free(dest);
		dest = get_next_line(fd);
	}
	if (close(fd) == -1)
		return (print_stderror(FAIL, 2, "error: close: ", strerror(errno)));
	return (SUCCESS);
}

int	biography(char *command)
{
	if (ft_strncmp(command, "tarchimb", 9) == 0)
		print_biography("srcs/custom/tarchimb.txt");
	else
		print_biography("srcs/custom/mliboz.txt");
	return (42);
}
