/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:05:46 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/15 09:35:32 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/*
	1: malloc what's inside the buffer (until '\n' or '\0) and return it
	2: move the data copied in dst off buffer using memmove
	3: free the old save
*/
char	*ft_putbuffer(char *buffer, char *save, char *pos)
{
	char	*dst;
	int		savelen;
	int		size;

	savelen = ft_strlen(save);
	size = savelen + pos - buffer + 1;
	dst = malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (0);
	dst = ft_memmove(dst, save, savelen + 1);
	ft_memmove(dst + savelen, buffer, pos - buffer + 1);
	buffer = ft_memmove(buffer, pos + 1, ft_strlen(pos));
	dst[size] = '\0';
	if (save)
		free(save);
	return (dst);
}

/*
	read fd and check the differents error
	1: if iread = -1 -> return NULL
	2: if iread = 0 -> either return NULL or save
	3: if iread > 0 -> contiunue the process by returning 2
*/
int	ft_read(char *buffer, char **save, char **pos, int fd)
{
	int		iread;

	*pos = *save;
	*save = ft_strjoin(*save, buffer);
	free(*pos);
	iread = read(fd, buffer, BUFFER_SIZE);
	buffer[iread] = '\0';
	if (iread <= 0)
	{	
		if (!**save || iread < 0)
		{
			free(*save);
			return (0);
		}
		return (1);
	}
	*pos = buffer - 1;
	return (2);
}

/*
	Get the next line of a fd, also can be use with multiple fd
	1: Check if the fd is valid and if buffer as been able to find enought memory
	2: read the file until having a line, EOF or an error
	3: call function to return line, free save and move buffer data already read
*/
char	*get_next_line(int fd)
{
	char static	buffer[OPEN_MAX][BUFFER_SIZE + 1];
	char		*pos;
	char		*save;
	int			iread;

	if (fd < 0 || fd > OPEN_MAX)
		return (0);
	save = ft_strdup("");
	if (!save)
		return (0);
	pos = buffer[fd];
	while (*pos != '\n')
	{
		if (!*pos)
		{
			iread = ft_read(buffer[fd], &save, &pos, fd);
			if (iread == 0)
				return (0);
			else if (iread == 1)
				return (save);
		}
		pos++;
	}
	return (ft_putbuffer(buffer[fd], save, pos));
}

// int	main(void)
// {
// 	int		fd;
// 	int		fd2;
// 	char	*str;
// 	char	*str2;

// 	fd = open("get_next_line.c", O_RDONLY);
// 	fd2 = open("get_next_line.h", O_RDONLY);
// 	str = get_next_line(fd);
// 	str2 = get_next_line(fd2);
// 	while (str || str2)
// 	{
// 		printf("%s", str);
// 		free(str);
// 		printf("%s", str2);
// 		free(str2);
// 		str = get_next_line(fd);
// 		str2 = get_next_line(fd2);
// 	}
// }

// int	main(void)
// {
// 	int		fd[42];
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	while (i < 42)
// 	{
// 		fd[i] = open("../bible.txt", O_RDONLY);
// 		i++;
// 	}
// 	i = 0;
// 	while ((str = get_next_line(fd[i])))
// 	{
// 		while (i < 42)
// 		{
// 			printf("(%d), %s", i, str);
// 			free(str);
// 			i++;
// 			str = get_next_line(fd[i]);
// 		}
// 		i = 0;
// 	}
// }
