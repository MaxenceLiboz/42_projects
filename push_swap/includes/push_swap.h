/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 08:06:02 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/10 11:22:01 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <libft.h>
# include <stdio.h>
# include <limits.h>

int			sa(t_list **a, int m, int p);
int			sb(t_list **b, int m, int p);
void		ss(t_list **a, t_list **b);
void		pa(t_list **a, t_list **b);
void		pb(t_list **a, t_list **b);
void		ra(t_list **a, int m);
void		rb(t_list **b, int m);
void		rr(t_list **a, t_list **b);
void		rra(t_list **a, int m);
void		rrb(t_list **b, int m);
void		rrr(t_list **a, t_list **b);

int			get_int(t_list **a, int argc, char **argv);

int			ft_lstsorted(t_list *lst);

long long	ft_atoll(const char *nptr);

int			get_index(t_list *lst, int value);
void		set_index(t_list **lst);
int			get_index_min(t_list *lst);
int			get_index_max(t_list *lst);
int			index_nearest(t_list *lst, int value);

void		small_sort(t_list **a);
void		mid_sort(t_list **a, t_list **b);
void		big_sort(t_list **a, t_list **b, int p);
void		radix(t_list **stack_a, t_list **stack_b);

#endif