/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:51:33 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/21 16:13:40 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Create a new node of lst_cmd
*/
t_lst_cmd	*lst_cmd_new(char **cmd, t_prg *prg)
{
	t_lst_cmd	*lst;

	lst = ft_malloc(prg, sizeof(t_lst_cmd) * 1);
	lst->cmd = cmd;
	lst->next = 0;
	return (lst);
}

/*
	Add a new node to the end of the list
*/
void	lst_cmd_add_back(t_lst_cmd **lst, t_lst_cmd *new_item)
{
	t_lst_cmd	*last;

	if (!new_item)
		return ;
	new_item->next = 0;
	if (!*lst)
		*lst = new_item;
	else
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new_item;
	}
}

/*
	Initialize the command structure
*/
t_lst_cmd	*lst_cmd_init(t_command *cmd, t_prg *prg)
{
	int			i;
	t_lst_cmd	*new;
	t_lst_cmd	*lst;

	i = pipes_size_cmd(*cmd);
	lst = NULL;
	while (i >= 0)
	{
		new = lst_cmd_new(get_cmd(cmd, prg), prg);
		lst_cmd_add_back(&lst, new);
		i--;
	}
	return (lst);
}

int	lst_cmd_size(t_lst_cmd *lst)
{
	int			size;
	t_lst_cmd	*tmp;

	if (!lst)
		return (0);
	size = 0;
	tmp = lst;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
