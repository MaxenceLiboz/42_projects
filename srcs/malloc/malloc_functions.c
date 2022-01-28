/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 08:44:01 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/28 14:15:24 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_malloc(t_list **mem, size_t size)
{
	void	*new_item;

	new_item = malloc(size);
	if (!size)
		ft_error_free(mem, "Malloc error occured");
	ft_lstadd_front(mem, ft_lstnew(new_item));
	return (new_item);
}

void	ft_error_free(t_list **mem, char *msg)
{
	ft_lstclear(mem, free);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(-1);
}
