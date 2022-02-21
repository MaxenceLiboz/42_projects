/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 08:44:01 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/21 11:50:58 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Malloc an element and add it to the garbage collector
*/
void	*ft_malloc(t_prg *prg, size_t size)
{
	void	*new_item;

	new_item = malloc(size);
	if (!new_item)
		ft_error_exit(prg, 1, "Malloc error occured");
	ft_lstadd_front(&prg->mem, ft_lstnew(new_item));
	return (new_item);
}

/*
	Print a message in STDOUT_FILENO, free garbage collector and exit -1
*/
int	ft_error_exit(t_prg *prg, int size, char *s1, ...)
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
	ft_lstclear_all(&prg->mem, &prg->old);
	exit(-1);
}
