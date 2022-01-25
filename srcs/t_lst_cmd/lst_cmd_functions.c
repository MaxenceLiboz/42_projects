/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxenceliboz <maxenceliboz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:51:33 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/01/25 09:19:45 by maxencelibo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lst_cmd	*lst_cmd_new(char **cmd, t_list **mem)
{
	t_lst_cmd	*lst;

	lst = ft_malloc(mem, sizeof(t_lst_cmd) * 1);
	lst->cmd = cmd;
	lst->next = 0;
	return (lst);
}

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

t_lst_cmd	*lst_cmd_init(t_command *cmd, t_list **mem)
{
	int			i;
	t_lst_cmd	*new;
	t_lst_cmd	*lst;

	i = pipes_size_cmd(*cmd);
	lst = NULL;
	while (i >= 0)
	{
		new = lst_cmd_new(get_cmd(cmd, mem), mem);
		lst_cmd_add_back(&lst, new);
		i--;
	}
	return (lst);
}

void	lst_cmd_put(t_lst_cmd	*lst)
{
	t_lst_cmd	*head;
	int			i;

	if (!lst)
		return ;
	i = 0;
	head = lst;
	while (head)
	{
		i = 0;
		while (head->cmd[i])
		{
			if (head->cmd[i + 1])
				printf("%s, ", head->cmd[i]);
			else
				printf("%s", head->cmd[i]);
			i++;
		}
		printf("\n");
		head = head->next;
	}
}

int	lst_cmd_size(t_lst_cmd *lst)
{
	int		size;

	if (!lst)
		return (0);
	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
