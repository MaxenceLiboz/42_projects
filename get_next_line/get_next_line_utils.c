/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:05:40 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/13 12:54:15 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
	Move in dst (size) data value of src
	1: if dst > src copy backward
	2: else copy forward
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int		i;

	if (!dst && !src)
		return (0);
	if (dst > src)
	{
		while (len--)
			*(unsigned char *)(dst + len) = *(unsigned char *)(src + len);
	}
	else
	{
		i = 0;
		while (len--)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	return (dst);
}

/*
	Allocate sufficent memory for char *str and return it
*/
char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	i++;
	dest = (char *)malloc(sizeof(char) * i);
	if (!dest)
		return (0);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
	Join s1 and s2 in a new malloc char * and return it.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	int		s1len;
	int		i;
	char	*dst;

	i = -1;
	if (!s1 || !s2)
		return (0);
	s1len = ft_strlen(s1);
	size = s1len + ft_strlen(s2);
	dst = malloc((size + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (s1[++i])
		dst[i] = s1[i];
	i = 0;
	while (s2[i])
	{
		dst[i + s1len] = s2[i];
		i++;
	}
	dst[i + s1len] = '\0';
	return (dst);
}

/*
	Get the length of a char *
*/
int	ft_strlen(const char *s)
{
	int		count;

	count = 0;
	while (s[count] != 0)
		count++;
	return (count);
}
