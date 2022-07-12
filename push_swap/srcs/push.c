/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:41:23 by maxencelibo       #+#    #+#             */
/*   Updated: 2021/12/17 15:04:36 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
	1: Push the top element of b on the top of a
*/
void	pa(t_list **a, t_list **b)
{
	t_list	*temp;

	if (!*b)
		return ;
	temp = *b;
	*b = (*b)->next;
	ft_lstadd_front(a, temp);
	ft_putstr_fd("pa\n", 1);
}

/*
	1: Push the top element of a on the top of b
*/
void	pb(t_list **a, t_list **b)
{
	t_list	*temp;

	if (!*a)
		return ;
	temp = *a;
	*a = (*a)->next;
	ft_lstadd_front(b, temp);
	ft_putstr_fd("pb\n", 1);
}
