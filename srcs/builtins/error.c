/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:01:48 by tarchimb          #+#    #+#             */
/*   Updated: 2022/01/13 02:01:43 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*error(char *str, int error)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return ((void *)(size_t)error);
}

// int	print_stderror(char	*s1, char *s2, char *s3)
// {
// 	ft_putstr_fd("bash: ", 2);
// 	ft_putstr_fd(s1, 2);
// 	ft_putstr_fd(s2, 2);
// 	ft_putstr_fd(s3, 2);
// 	ft_putstr_fd("\n", 2);
// 	return (0);
// }

// first arg is size of arg, set second one to 0, then add string
int	print_stderror(int size, char *s1, ...)
{
	va_list	arg;

	va_start(arg, s1);
	while (size--)
		ft_putstr_fd(va_arg(arg, char *), 2);
	va_end(arg);
	return (0);
}
