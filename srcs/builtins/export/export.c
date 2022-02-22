/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 11:40:44 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/22 11:17:22 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Get the path of the built in .c files
*/
static int	get_builtin_path(t_lst_env *export, t_lst_env *env, t_prg *prg)
{
	char	*path;

	path = getenv("_");
	if (!path)
		return (print_stderror(FALSE, 1, "can't get env variable, break"));
	path = sub_string(path, 0, ft_strlen(path) - 11, prg).str;
	export->var = join_string("srcs/builtins/",
			export->var.str, prg);
	export->var = join_string(path,
			export->var.str, prg);
	env->var = join_string("srcs/builtins/",
			env->var.str, prg);
	env->var = join_string(path,
			env->var.str, prg);
	return (TRUE);
}

/*
	Try all the PATH with out command to see witch one will execute
*/
void	try_path(t_prg *prg, t_lst_env *export, t_lst_env *env)
{
	int			i;
	t_string	cmd;

	i = -1;
	trim_string(&export->var, prg, " ");
	trim_string(&env->var, prg, " ");
	if (is_builtin(prg) == TRUE)
	{
		get_builtin_path(export, env, prg);
		return ;
	}
	if (prg->paths == NULL)
		return ;
	while (prg->paths[++i])
	{
		cmd = join_string(prg->paths[i], export->var.str, prg);
		if (access(cmd.str, X_OK) == 0)
		{
			export->var.str = cmd.str;
			env->var.str = cmd.str;
			return ;
		}
	}
}

/*
	Init the _ variable each time a command is run
	Take the path or the last argument of the lastest command
*/
void	init_env__(t_prg *prg)
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
	while (--i && prg->cmd.command.str[i] == ' ')
		;
	while (--i && prg->cmd.command.str[i] != ' ')
		;
	if (prg->cmd.command.str[i] == ' ')
		i++;
	export->var = sub_string(prg->cmd.command.str, i,
			ft_strlen(prg->cmd.command.str), prg);
	env->var = sub_string(prg->cmd.command.str, i,
			ft_strlen(prg->cmd.command.str) - i + 1, prg);
	try_path(prg, export, env);
}

/*
	Reporducing export command in bash
*/
int	ft_export(t_head_env *head, char **command, t_prg *prg)
{
	char	*var_name;
	int		i;

	i = 0;
	if (!command[i + 1])
		return (print_export(head));
	while (command[++i])
	{
		var_name = sub_string(command[i], 0, ft_strchr_len(command[i], '='),
				prg).str;
		if (control_args(var_name) == SUCCESS)
		{
			if (lst_env_find_name_var(head->export, var_name).str == 0)
				add_elem_to_lst(command[i], head, prg);
			else
				if (ft_strchr(command[i], '=') != 0)
					replace_elem_of_lst(head, command[i], var_name, prg);
		}
		else
			print_stderror(1, 3, "export: `", command[i],
				"': not a valid identifier");
	}
	return (0);
}
