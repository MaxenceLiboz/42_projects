/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 08:20:07 by maxencelibo       #+#    #+#             */
/*   Updated: 2022/02/16 11:07:00 by tarchimb         ###   ########.fr       */
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

static int	get_builtin_path(t_lst_env *export, t_lst_env *env, t_list **mem)
{
	char	*path;

	path = getenv("_");
	if (!path)
		return (print_stderror(FALSE, 1, "can't get env variable, break"));
	path = sub_string(path, 0, ft_strlen(path) - 11, mem).str;
	export->var = join_string("srcs/builtins/",
			export->var.str, mem);
	export->var = join_string(path,
			export->var.str, mem);
	env->var = join_string("srcs/builtins/",
			env->var.str, mem);
	env->var = join_string(path,
			env->var.str, mem);
	return (TRUE);
}

int	try_path(t_prg *prg, t_lst_env *export, t_lst_env *env)
{
	int			i;
	t_string	cmd;

	i = -1;
	if (is_builtin(prg) == TRUE)
	{
		if (get_builtin_path(export, env, &prg->mem) == TRUE)
			return (TRUE);
		return (FALSE);
	}
	while (prg->paths[++i])
	{
		cmd = join_string(prg->paths[i], export->var.str, &prg->mem);
		if (access(cmd.str, X_OK) == 0)
		{
			export->var.str = cmd.str;
			env->var.str = cmd.str;
			return (TRUE);
		}
	}
	return (FALSE);
}

static void	init_env__(t_prg *prg)
{
	int			i;
	t_lst_env	*export;
	t_lst_env	*env;

	i = 0;
	export = prg->env.export;
	env = prg->env.env;
	while (env && ft_strncmp(env->name_var.str, "_", 2) != 0)
		env = env->next;
	while (export && ft_strncmp(export->name_var.str, "_", 2) != 0)
		export = export->next;
	while (prg->cmd.command.str[i])
		i++;
	while (--i && prg->cmd.command.str[i] != ' ')
		;
	if (prg->cmd.command.str[i] == ' ')
		i++;
	export->var = sub_string(prg->cmd.command.str, i,
			ft_strlen(prg->cmd.command.str), &prg->mem);
	env->var = sub_string(prg->cmd.command.str, i,
			ft_strlen(prg->cmd.command.str) - i + 1, &prg->mem);
	if (try_path(prg, export, env) == TRUE)
		return ;
}

static void	init_prg(t_prg *prg)
{
	errno = 0;
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
	char	**envp;
	int		status;

	init_prg(prg);
	init_env__(prg);
	envp = lst_env_to_array(prg->env.env, &prg->mem);
	prg->fd.pipe_nb = lst_cmd_size(prg->lst_cmd);
	ft_pipex(prg, envp);
	while (waitpid(-1, &status, 0) != -1)
		;
	if (WIFEXITED(status))
		g_returnvalue = WEXITSTATUS(status);
	ft_double_dup(prg->fd.stdin_save, prg->fd.stdout_save, &prg->mem);
	close(prg->fd.stdin_save);
	close(prg->fd.stdout_save);
	return (g_returnvalue);
}
