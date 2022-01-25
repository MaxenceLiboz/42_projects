/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:02:00 by mliboz            #+#    #+#             */
/*   Updated: 2022/01/25 07:47:00 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// we exit program if we unset PWD, or TERM_SESSION_ID, that is a problem
// Need to reset OLDPWD at each command
//At start, we need to set OLDPWD to 0;
//need to set PWD at each loop, unless PWD is unset
int	main(int argc, char **argv, char **envp)
{
	t_prg	prg;
	int		ret;
	char	*tmp;

	(void)argc;
	(void)argv;
	prg.mem = 0;
	set_export(envp, &prg.env, &prg.mem);
	ret = tgetent(NULL, getenv("TERM"));
	while (1)
	{
		prg.prompt = create_prompt(&prg.mem);
		prg.cmd.command.str = readline(prg.prompt.str);
		// tmp = tgetstr("3", &prg.cmd.command.str);
		// tputs(tmp, 10, putchar);
		if (*prg.cmd.command.str)
			add_history(prg.cmd.command.str);
		init_string(&prg.cmd.command, prg.cmd.command.str, FALSE, &prg.mem);
		ft_lstadd_front(&prg.mem, ft_lstnew(prg.cmd.command.str));
		if (*prg.cmd.command.str)
		{
			prg.lst_cmd = create_command(&prg);
			// lst_cmd_put(cmd);
			exec_builtin(prg.lst_cmd->cmd, &prg.env, &prg.mem);
		}
		reinit_command(&prg.cmd);
	}
	return (ft_lstclear(&prg.mem, free));
}
