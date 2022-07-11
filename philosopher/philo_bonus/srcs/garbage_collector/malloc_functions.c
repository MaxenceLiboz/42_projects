/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 08:44:01 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/03/09 13:14:06 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>

/*
	Malloc an element and add it to the garbage collector
*/
void	*ft_malloc(t_table *table, size_t size)
{
	void	*new_item;
	t_list	*new_lst;

	new_item = malloc(size);
	if (!new_item)
		ft_error_exit(table, 1, "Malloc error occured");
	new_lst = ft_lstnew(new_item);
	if (new_lst == NULL)
	{
		free(new_item);
		ft_error_exit(table, 1, "Malloc error occured");
	}
	ft_lstadd_front(&table->mem, new_lst);
	return (new_item);
}

/*
	Print a message in STDOUT_FILENO, free garbage collector and exit -1
*/
int	ft_error_exit(t_table *table, int size, char *s1, ...)
{
	va_list	arg;

	va_start(arg, s1);
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
	ft_lstclear(&table->mem);
	exit(-1);
}
