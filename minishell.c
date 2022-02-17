/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/02/17 11:39:30 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Handle SIGINT for our main program
*/
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

/*
	Clear garbage collector
*/
int	ft_lstclear_all(t_list **lst, struct termios *old)
{
	t_list	*save;

	if (tcsetattr(0, TCSANOW, old) == -1)
		return (ft_lstclear_all(lst, old));
	rl_clear_history();
	if (!*lst)
		return (0);
	while ((*lst)->next)
	{
		save = (*lst)->next;
		if ((*lst)->content)
			free((*lst)->content);
		free(*lst);
		*lst = save;
	}
	*lst = 0;
	return (0);
}

static void	launch_minishell(t_prg *prg)
{
	char	*line;

	line = NULL;
	while (1)
	{
		set_signal();
		prg->prompt = create_prompt(prg->pwd, prg);
		line = readline(prg->prompt.str);
		if (!line)
			ft_exit(NULL, prg);
		init_string(&prg->cmd.command, line, TRUE, prg);
		free(line);
		if (*prg->cmd.command.str)
			add_history(prg->cmd.command.str);
		if (*prg->cmd.command.str)
		{
			prg->lst_cmd = create_command(prg);
			if (prg->lst_cmd && *prg->lst_cmd->cmd[0] != 0)
				exec_command(prg);
		}
		reinit_command(&prg->cmd);
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
	launch_minishell(&prg);
	return (ft_lstclear_all(&prg.mem, &prg.old));
}
