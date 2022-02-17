/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:20:07 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/17 11:30:42 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Convert the PATH stored in our variable to a char ** list 
*/
static char	**get_path(t_lst_env *export, t_prg *prg)
{
	t_string	envp_path;
	t_string	*paths;
	char		**dst;
	int			i;

	i = 0;
	envp_path = lst_env_find_name_var(export, "PATH");
	if (!envp_path.str)
		return (0);
	paths = split_string(envp_path.str, ':', prg);
	if (!paths)
		ft_error_exit(prg, 1, "exit: envp_path.str: error not found");
	while (paths[i].str)
	{
		add_string(&paths[i], "/", paths[i].size - 1, prg);
		i++;
	}
	dst = strings_to_array(paths, prg);
	return (dst);
}

/*
	Init the program everytime a command is run
*/
static void	init_prg(t_prg *prg)
{
	errno = 0;
	prg->fd.stdin_save = dup(STDIN_FILENO);
	if (prg->fd.stdin_save == -1)
		ft_error_exit(prg, 1, "exit: STDIN_FILENO save failed");
	prg->fd.stdout_save = dup(STDOUT_FILENO);
	if (prg->fd.stdout_save == -1)
		ft_error_exit(prg, 1, "exit: STDOUT_FILENO save failed");
	prg->fd.fd_in = 0;
	prg->fd.fd_out = 0;
	prg->paths = get_path(prg->env.export, prg);
}

/*
	Execute the command previously parsed
*/
int	exec_command(t_prg *prg)
{
	char	**envp;
	int		status;

	init_prg(prg);
	init_env__(prg);
	envp = lst_env_to_array(prg->env.env, prg);
	prg->fd.pipe_nb = lst_cmd_size(prg->lst_cmd);
	ft_pipex(prg, envp);
	while (waitpid(-1, &status, 0) != -1)
		;
	if (WIFEXITED(status))
		g_returnvalue = WEXITSTATUS(status);
	ft_double_dup(prg->fd.stdin_save, prg->fd.stdout_save, prg);
	ft_close(prg->fd.stdin_save, prg);
	ft_close(prg->fd.stdout_save, prg);
	return (g_returnvalue);
}
