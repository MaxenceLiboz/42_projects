/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsorted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 08:29:44 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/18 08:35:23 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
	1: Check if the list is sorted
*/
int	ft_lstsorted(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
	{
		if (!(lst->content < lst->next->content))
			return (0);
		lst = lst->next;
	}
	return (1);
}
