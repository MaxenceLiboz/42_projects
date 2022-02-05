/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:01:48 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/04 18:16:22 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*error(char *str, int error)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return ((void *)(size_t)error);
}

// first arg is size of arg, set second one to 0, then add string
int	print_stderror(int error, int size, char *s1, ...)
{
	va_list	arg;

	va_start(arg, s1);
	ft_putstr_fd("minishell: ", 2);
	if (s1)
	{
		ft_putstr_fd(s1, 2);
		size--;
	}
	while (size--)
		ft_putstr_fd(va_arg(arg, char *), 2);
	ft_putstr_fd("\n", 2);
	va_end(arg);
	errno = 0;
	return (error);
}
