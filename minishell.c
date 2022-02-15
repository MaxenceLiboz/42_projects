/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/14 10:57:24 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handler_main(int signum)
{
	if (signum == SIGINT)
	{
		g_returnvalue = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

// we exit program if we unset PWD, or TERM_SESSION_ID, that is a problem
// Need to reset OLDPWD at each command
//At start, we need to set OLDPWD to 0;
//need to set PWD at each loop, unless PWD is unset
int	main(int argc, char **argv, char **envp)
{
	t_prg			prg;

	prg.mem = 0;
	if (argc > 1 || argv[1])
		return (print_stderror(2, 2, argv[1], ": invalid option"));
	initialization(envp, &prg);
	while (1)
	{
		set_signal();
		prg.prompt = create_prompt(prg.pwd, &prg.mem);
		prg.cmd.command.str = readline(prg.prompt.str);
		if (!prg.cmd.command.str)
		{
			tcsetattr(0, TCSANOW, &prg.old);
			ft_exit(NULL, &prg);
		}
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
	tcsetattr(0, TCSANOW, &prg.old);
	rl_clear_history();
	return (ft_lstclear(&prg.mem, free));
}
