/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:27:40 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/13 13:00:09 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strdup(char *src);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *s);
char	*get_next_line(int fd);

#endif