/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:38:32 by mliboz            #+#    #+#             */
/*   Updated: 2021/12/28 15:53:34 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*save;

	if (!*lst)
		return (0);
	while (*lst)
	{
		save = (*lst)->next;
		(void)del;
		free(*lst);
		*lst = save;
	}
	*lst = 0;
	return (0);
}
