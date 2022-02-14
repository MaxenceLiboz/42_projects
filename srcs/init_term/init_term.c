/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:31:57 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/14 14:44:03 by tarchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	inittermios(struct termios *old)
{
	struct termios	new;

	tcgetattr(0, old);
	new = *old;
	new.c_lflag &= (ECHO | ISIG | ICANON);
	tcsetattr(0, TCSANOW, &new);
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

static void	set_term_env(t_list **mem, struct termios *old)
{
	char	*tmp;

	(void)mem;
	// if (tgetent(NULL, getenv("TERM")) == ERR)
	// 	ft_error_exit(mem, 1, "getent: error");
	inittermios(old);
	tgetent(NULL, getenv("TERM"));
	tmp = tgetstr("cl", NULL);
	tputs(tmp, 0, putchar);
	// if (tmp == NULL)
	// 	ft_error_exit(mem, 1, "tgetstr: error");
}

int	initialization(char **envp, t_prg *prg)
{
	set_term_env(&prg->mem, &prg->old);
	print_title();
	set_export(envp, &prg->env, &prg->mem);
	init_pwd(&prg->pwd, &prg->mem);
	return (0);
}
