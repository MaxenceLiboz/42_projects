/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:31:57 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/21 13:53:12 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	Init our terminal termios
*/
static void	inittermios(struct termios *old, t_prg *prg)
{
	struct termios	new;

	if (tcgetattr(0, old) == ERR)
		ft_error_exit(prg, 2, "tcgetattr: ", strerror(errno));
	new = *old;
	new.c_lflag &= (ECHO | ISIG | ICANON);
	if (tcsetattr(0, TCSANOW, &new) == ERR)
		ft_error_exit(prg, 2, "tcsetattr: ", strerror(errno));
}

static void	init_pwd(t_string *pwd, t_prg *prg)
{
	char	*getpwd;

	getpwd = getcwd(NULL, 0);
	if (getpwd == NULL)
		ft_error_exit(prg, 1, "getcwd: error initializing pwd");
	init_string(pwd, getpwd, TRUE, prg);
	free(getpwd);
}

/*
	Use inittermios();
	Set the environment for our minishell
*/
static void	set_term_env(t_prg *prg, struct termios *old)
{
	char	*tmp;

	inittermios(old, prg);
	tgetent(NULL, getenv("TERM"));
	// if (tgetent(NULL, getenv("TERM")) == ERR)
	// 	ft_error_exit(prg, 1, "getent: error");
	tmp = tgetstr("cl", NULL);
	// if (tmp == NULL)
	// 	ft_error_exit(prg, 1, "tgetstr: error");
	tputs(tmp, 10, putchar);
	// if (tputs(tmp, 10, putchar) == ERR)
	// 	ft_error_exit(prg, 1, "tputs: error");
}

/*
	Initiate the terminal attributs, set env variables
*/
int	initialization(char **envp, t_prg *prg)
{
	set_export(envp, &prg->env, prg);
	set_term_env(prg, &prg->old);
	print_title();
	init_pwd(&prg->pwd, prg);
	return (0);
}
