/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:20:36 by mliboz            #+#    #+#             */
/*   Updated: 2021/11/02 13:23:55 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90)
		|| (c >= 48 && c <= 57))
		return (1);
	else
		return (0);
}