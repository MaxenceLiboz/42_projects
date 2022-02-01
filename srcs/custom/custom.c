/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 21:49:02 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/01 12:55:51 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_title(void)
{
	int		fd;
	char	*dest;

	fd = open("srcs/custom/title.txt", O_RDONLY);
	if (fd < 0)
		return ;
	dest = get_next_line(fd);
	while (dest)
	{
		printf("\e[0;32m %s", dest);
		free(dest);
		dest = get_next_line(fd);
	}
	printf("\t\t\t\t\t\t\t\t\t \e[0;37m by tarchimb and mliboz\n");
	if (close(fd) == -1)
		print_stderror(0, 1, strerror(errno));
	return ;
}

void	print_biography(char *user)
{
	int		fd;
	char	*dest;

	if (access(user, F_OK | R_OK) == 0)
		fd = open(user, O_RDONLY);
	else
		return ;
	if (fd < 0)
		return ;
	dest = get_next_line(fd);
	while (dest)
	{
		printf("%s", dest);
		free(dest);
		dest = get_next_line(fd);
	}
	close(fd);
	return ;
}

int	biography(char *command)
{
	if (ft_strncmp(command, "tarchimb", 9) == 0)
		print_biography("srcs/custom/tarchimb.txt");
	else
		print_biography("srcs/custom/mliboz.txt");
	return (42);
}