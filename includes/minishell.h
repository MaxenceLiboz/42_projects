/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mliboz <mliboz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:45:00 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/01 08:21:37 by mliboz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h> 
# include <unistd.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <signal.h>

#define TEST_PS(expectation, ft) printf("Expected:\t\e[0;34m%s\e[0m\nGot:\t\t\e[0;34m", expectation); ft; printf("\e[0m\n");
#define TEST_S(expectation, str) ft_strncmp(expectation, str, ft_strlen(expectation) + 1) == 0 ? printf("\e[0;32mOK\e[0m\n") : printf("\e[0;31mFALSE\e[0m\nExpected:\t\e[0;34m%s\e[0m\nGot:\t\t\e[0;34m%s\e[0m\n\n", expectation, str);
#define TEST_I(expectation, int) expectation == int ? printf("\e[0;32mOK\e[0m\n") : printf("\e[0;31mFALSE\e[0m\nExpected:\t\e[0;34m%d\e[0m\nGot:\t\t\e[0;34m%d\e[0m\n\n", expectation, int);

# define BLUE "\033[0;34m"
# define END_COLOR "\033[0m"
# define TRUE 1
# define FALSE 0
# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef int	t_bool;

/**************** Malloc  ****************/

void		*ft_malloc(t_list **mem, size_t size);
void		ft_error_free(t_list **mem, char *msg);

/**************** String  ****************/
typedef struct s_string
{
	char	*str;
	int		size;
	int		max_size;
}	t_string;

void		init_string(t_string *string, char *src, t_bool to_malloc,
				t_list **mem);
void		reinit_string(t_string *string);
void		realloc_string(t_string *string, t_list **mem);
void		cat_string(t_string *string, t_string cat);
void		dup_string(t_string *string, char *src, int index, t_list **mem);
void		replace_string(t_string *string, int *indexs, char *replace_with,
				t_list **mem);
t_string	sub_string(char *src, size_t start, size_t size, t_list **mem);
void		erase_string(t_string *string, char *to_replace, size_t start,
				t_list **mem);
void		add_string(t_string *string, char *to_add, size_t index,
				t_list **mem);
t_string	*split_string(char *s, char c, t_list **mem);
char		**strings_to_array(t_string *strings, t_list **mem);
t_string	join_string(char *s1, char *s2, t_list **mem);

/**************** Command ********/
typedef struct s_command
{
	t_string	*array;
	t_string	command;
	int			size;
	int			max_size;
	int			index;
}	t_command;

void		init_command(t_command *array_string, int size, int to_malloc,
				t_list **mem);
void		reinit_command(t_command *array);
char		**get_cmd(t_command *cmd, t_list **mem);
int			pipes_size_cmd(t_command cmd);

/**************** ENV ********************/
typedef struct s_lst_env
{
	t_string			name_var;
	t_string			var;
	struct s_lst_env	*next;
}	t_lst_env;

t_lst_env	*lst_env_new(char *name_var, char *var, t_list **mem);
void		lst_env_add_back(t_lst_env **lst, t_lst_env *new);
void		lst_env_add_front(t_lst_env **lst, t_lst_env *new);
int			lst_env_clear(t_lst_env **lst);
void		lst_env_delone(t_lst_env *prev, t_lst_env *to_del,
				t_lst_env **head);
int			lst_env_size(t_lst_env *lst);
void		lst_env_swap(t_lst_env **head, t_lst_env **next);
void		lst_env_sort(t_lst_env **env);
t_string	lst_env_find_name_var(t_lst_env *env, char *str);
char		**lst_env_to_array(t_lst_env *env, t_list **mem);

typedef struct s_head_env
{
	t_lst_env			*env;
	t_lst_env			*export;
}	t_head_env;

/**************** t_lst_command ****************/
typedef struct s_lst_cmd
{
	char				**cmd;
	struct s_lst_cmd	*next;
}	t_lst_cmd;
t_lst_cmd	*lst_cmd_new(char **cmd, t_list **mem);
void		lst_cmd_add_back(t_lst_cmd **lst, t_lst_cmd *new_item);
int			lst_cmd_clear(t_lst_cmd **lst);
void		lst_cmd_put(t_lst_cmd	*lst);
t_lst_cmd	*lst_cmd_init(t_command *cmd, t_list **mem);
int			lst_cmd_size(t_lst_cmd *lst);

/**************** custom ****************/

void		print_title(void);
int			biography(char *command);

/**************** fd ********/
typedef struct s_fd
{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	int		pipe_nb;
}	t_fd;

/**************** t_prg ***********************/
typedef struct s_prg
{
	t_head_env	env;
	t_string	prompt;
	t_command	cmd;
	t_lst_cmd	*lst_cmd;
	t_list		*mem;
	char		**paths;
	t_fd		fd;
}	t_prg;

/**************** t_pipe ***********************/



/**************** set_env ***********************/
void		set_term_env(void);
void		get_signal(void);

/**************** OPTIONAL ****************/
void		ft_free(char **str);
int			print_stderror(int error, int size, char *s1, ...);

/**************** Built in ********/
int			exec_builtin(char **command, t_head_env *head, t_prg *prg);
int			control_args(char *str);
int			print_export(t_head_env *head);
int			ft_export(t_head_env *head, char **command, t_list **mem);
int			control_args(char *str);
int			ft_env(t_lst_env *lst, char **command);
int			ft_unset(t_head_env **head, char **command);
int			ft_echo(char **str);
int			ft_cd(char **str, t_head_env *head, t_list **mem);
int			ft_pwd(char **str);
int			print_export(t_head_env *head);
void		ft_exit(char **str, t_list **mem);

/**************** Parsing ******************/
t_string	create_prompt(t_list **mem);
t_lst_cmd	*create_command(t_prg *prg);
void		split_wog(t_prg *prg, char c);
int			count_split_wog(const char *str, char charset);
t_bool		check_quotes(t_string cmd);
t_bool		check_pipes(t_command cmd);
t_bool		check_chevrons(t_string *cmd, t_list **mem);

int			set_export(char **envp, t_head_env *head, t_list **mem);

/**************** Exec_command *************/
int			exec_command(t_prg *prg);
int			check_cmd(t_prg *prg, t_lst_cmd *cmd);
char		**f_cmd(char **cmd, t_list **mem);
void		double_dup(int fd1, int fd2, t_list **mem);

/**************** ARGS *************/
void		change_arg_command(t_prg *prg, t_string *str);
void		find_arg_and_replace(t_prg *prg, t_string *arg, int start,
				t_string *str);
t_bool		is_arg(char *arg, int *start);
#endif