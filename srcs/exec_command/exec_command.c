/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:20:07 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/05 11:22:42 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**get_path(t_lst_env *export, t_list **mem)
{
	t_string	envp_path;
	t_string	*paths;
	char		**dst;
	int			i;

	i = 0;
	envp_path = lst_env_find_name_var(export, "PATH");
	if (!envp_path.str)
		return (0);
	paths = split_string(envp_path.str, ':', mem);
	if (!paths)
		ft_error_free(mem, "envp_path.str: error not found");
	while (paths[i].str)
	{
		add_string(&paths[i], "/", paths[i].size - 1, mem);
		i++;
	}
	dst = strings_to_array(paths, mem);
	return (dst);
}

static void	init_prg(t_prg *prg)
{
	errno = 0;
	prg->return_value = 0;
	prg->fd.stdin_save = dup(STDIN_FILENO);
	if (prg->fd.stdin_save == -1)
		ft_error_free(&prg->mem, "error: STDIN_FILENO save failed");
	prg->fd.stdout_save = dup(STDOUT_FILENO);
	if (prg->fd.stdout_save == -1)
		ft_error_free(&prg->mem, "error: STDOUT_FILENO save failed");
	prg->fd.fd_in = 0;
	prg->fd.fd_out = 0;
	prg->paths = get_path(prg->env.export, &prg->mem);
}

int	exec_command(t_prg *prg)
{
	init_prg(prg);
	if (lst_cmd_size(prg->lst_cmd) == 1)
		prg->return_value = ft_exec_one(prg);
	else
		ft_pipex(prg);
	ft_double_dup(prg->fd.stdin_save, prg->fd.stdout_save, &prg->mem);
	close(prg->fd.stdin_save);
	close(prg->fd.stdout_save);
	return (prg->return_value);
}
