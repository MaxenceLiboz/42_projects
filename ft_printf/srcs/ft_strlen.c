/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:27:00 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/18 09:45:42 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Get the lenght of a string
*/
int	ft_strlen(const char *s)
{
	int		count;

	count = 0;
	while (s[count] != 0)
		count++;
	return (count);
}
