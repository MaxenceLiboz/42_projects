/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:05:46 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/05 17:02:52 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		size;
	int		i;
	char	*dst;

	i = -1;
	if (!s2 && !s1)
		return (0);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	size = ft_strlen(s1) + ft_strlen(s2);
	dst = malloc((size + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (s1[++i])
		dst[i] = s1[i];
	i = -1;
	while (s2[++i])
		dst[i + ft_strlen(s1)] = s2[i];
	dst[i + ft_strlen(s1)] = '\0';
	return (dst);
}

/*
	1: malloc what's inside the buffer (until '\n' or '\0) and return it
	2: move the data copied in dst off buffer using memmove
	3: free the old save
*/
static char	*ft_putbuffer(char *buffer, char *save, char *pos)
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
static int	ft_read(char *buffer, char **save, char **pos, int fd)
{
	int		iread;

	*pos = *save;
	*save = ft_strjoin_gnl(*save, buffer);
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
