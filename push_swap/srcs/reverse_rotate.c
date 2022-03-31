/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:42:49 by maxencelibo       #+#    #+#             */
/*   Updated: 2021/12/17 15:06:26 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <push_swap.h>

/*
	1: If lst doesn't exist or we have only one element return
	2: Make the last element of a become the first
*/
void	rra(t_list **a, int m)
{
	t_list	*last;
	t_list	*head;

	if (!*a || !(*a)->next)
		return ;
	last = ft_lstlast(*a);
	head = *a;
	while (head->next->next)
		head = head->next;
	head->next = 0;
	last->next = *a;
	*a = last;
	if (m != 0)
		ft_putstr_fd("rra\n", 1);
}

/*
	1: If lst doesn't exist or we have only one element return
	2: Make the last element of b become the first
*/
void	rrb(t_list **b, int m)
{
	t_list	*last;
	t_list	*head;

	if (!*b || !(*b)->next)
		return ;
	last = ft_lstlast(*b);
	head = *b;
	while (head->next->next)
		head = head->next;
	head->next = 0;
	last->next = *b;
	*b = last;
	if (m != 0)
		ft_putstr_fd("rrb\n", 1);
}

/*
	1: Use reverse rotate for both stack
*/
void	rrr(t_list **a, t_list **b)
{
	rra(a, 0);
	rrb(b, 0);
	ft_putstr_fd("rrr\n", 1);
}
