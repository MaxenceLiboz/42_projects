/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/09 14:58:04 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	get_signal(t_list **mem)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = 0;
	signal(SIGQUIT, SIG_IGN);
	if (sigaction(SIGINT, &sa, NULL) == ERR)
		ft_error_exit(mem, 2, "sigaction: ", strerror(errno));
}

static void	init_pwd(t_string *pwd, t_list **mem)
{
	char	*getpwd;

	getpwd = getcwd(NULL, 0);
	if (getpwd == NULL)
		ft_error_exit(mem, 1, "getcwd: error initializing pwd");
	init_string(pwd, getpwd, TRUE, mem);
	free(getpwd);
}

// we exit program if we unset PWD, or TERM_SESSION_ID, that is a problem
// Need to reset OLDPWD at each command
//At start, we need to set OLDPWD to 0;
//need to set PWD at each loop, unless PWD is unset
int	main(int argc, char **argv, char **envp)
{
	t_prg	prg;
	int		i = 5;

	(void)argc;
	(void)argv;
	prg.mem = 0;
	set_export(envp, &prg.env, &prg.mem);
	set_term_env(&prg.mem);
	print_title();
	init_pwd(&prg.pwd, &prg.mem);
	while (i--)
	{
		get_signal(&prg.mem);
		prg.prompt = create_prompt(prg.pwd, &prg.mem);
		prg.cmd.command.str = readline(prg.prompt.str);
		if (!prg.cmd.command.str)
			ft_exit(NULL, &prg.mem);
		if (*prg.cmd.command.str)
			add_history(prg.cmd.command.str);
		init_string(&prg.cmd.command, prg.cmd.command.str, FALSE, &prg.mem);
		ft_lstadd_front(&prg.mem, ft_lstnew(prg.cmd.command.str));
		if (*prg.cmd.command.str)
		{
			prg.lst_cmd = create_command(&prg);
			if (prg.lst_cmd && *prg.lst_cmd->cmd[0] != 0)
				exec_command(&prg);
		}
		reinit_command(&prg.cmd);
	}
	rl_clear_history();
	return (ft_lstclear(&prg.mem, free));
}
