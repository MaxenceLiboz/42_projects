/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 09:35:58 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/08 11:01:47 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

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
