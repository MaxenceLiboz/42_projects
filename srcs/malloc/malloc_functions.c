/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 08:44:01 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/16 18:54:20 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_malloc(t_list **mem, size_t size)
{
	void	*new_item;
	static int i = 0;

	new_item = malloc(size);
	if (!new_item)
		ft_error_free(mem, "Malloc error occured");
	ft_lstadd_front(mem, ft_lstnew(new_item));
	return (new_item);
}

void	ft_error_free(t_list **mem, char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	ft_lstclear(mem, free);
	exit(-1);
}

/*
	Print a message in STDOUT_FILENO, free garbage collector and exit -1
*/

int	ft_error_exit(t_list **mem, int size, char *s1, ...)
{
	va_list	arg;

	va_start(arg, s1);
	ft_putstr_fd("minishell: exit: ", 2);
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
	ft_lstclear(mem, free);
	exit(-1);
}
