/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarchimb <tarchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 15:45:00 by tarchimb          #+#    #+#             */
/*   Updated: 2022/02/22 11:16:28 by tarchimb         ###   ########.fr       */
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

# define BLUE "\001\033[0;34m\002"
# define END_COLOR "\001\033[0m\002"
# define YELLOW "\001\033[38;5;214m\002"
# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define FAIL 1

typedef int	t_bool;
int			g_returnvalue;

/**************** String  ****************/
typedef struct s_string
{
	char	*str;
	int		size;
	int		max_size;
}	t_string;

/**************** t_heredoc  ****************/

typedef struct s_heredoc
{
	t_string	*table;
	int			size;
	int			malloc_size;
	int			index;
}	t_heredoc;

/**************** Command ********/
typedef struct s_command
{
	t_string	*array;
	t_string	command;
	int			size;
	int			max_size;
	int			index;
}	t_command;

/**************** ENV ********************/
typedef struct s_lst_env
{
	t_string			name_var;
	t_string			var;
	struct s_lst_env	*next;
}	t_lst_env;

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

/**************** fd ********/
typedef struct s_fd
{
	int		fd[2];
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	int		pipe_nb;
	int		stdin_save;
	int		stdout_save;
}	t_fd;

/**************** t_prg ***********************/
typedef struct s_prg
{
	t_head_env		env;
	t_string		prompt;
	t_command		cmd;
	t_lst_cmd		*lst_cmd;
	t_list			*mem;
	char			**paths;
	t_fd			fd;
	int				return_value;
	t_heredoc		heredocs;
	t_string		pwd;
	struct termios	old;
}	t_prg;

/**************** STRINGS *****************/
void		init_string(t_string *string, char *src, t_bool to_malloc,
				t_prg *prg);
void		realloc_string(t_string *string, t_prg *prg);
void		cat_string(t_string *string, t_string cat);
void		dup_string(t_string *string, char *src, int index, t_prg *prg);
void		replace_string(t_string *string, int *indexs, char *replace_with,
				t_prg *prg);
t_string	sub_string(char *src, size_t start, size_t size, t_prg *prg);
void		erase_string(t_string *string, char *to_erase, size_t start,
				t_prg *prg);
void		add_string(t_string *string, char *to_add, size_t index,
				t_prg *prg);
t_string	*split_string(char *s, char c, t_prg *prg);
char		**strings_to_array(t_string *strings, t_prg *prg);
t_string	join_string(char *s1, char *s2, t_prg *prg);
void		trim_string(t_string *string, t_prg *prg, char *to_trim);

/**************** ENV *****************/
t_lst_env	*lst_env_new(char *name_var, char *var, t_prg *prg);
void		lst_env_add_back(t_lst_env **lst, t_lst_env *new);
void		lst_env_add_front(t_lst_env **lst, t_lst_env *new);
int			lst_env_clear(t_lst_env **lst);
void		lst_env_delone(t_lst_env *prev, t_lst_env *to_del,
				t_lst_env **head);
int			lst_env_size(t_lst_env *lst);
void		lst_env_swap(t_lst_env **head, t_lst_env **next);
void		lst_env_sort(t_lst_env **env);
t_string	lst_env_find_name_var(t_lst_env *env, char *str);
char		**lst_env_to_array(t_lst_env *env, t_prg *prg);

/**************** t_lst_cmd *****************/
t_lst_cmd	*lst_cmd_new(char **cmd, t_prg *prg);
void		lst_cmd_add_back(t_lst_cmd **lst, t_lst_cmd *new_item);
int			lst_cmd_clear(t_lst_cmd **lst);
t_lst_cmd	*lst_cmd_init(t_command *cmd, t_prg *prg);
int			lst_cmd_size(t_lst_cmd *lst);

/**************** Command *****************/
void		init_command(t_command *array_string, int size, int to_malloc,
				t_prg *prg);
void		reinit_command(t_command *array);
char		**get_cmd(t_command *cmd, t_prg *prg);
int			pipes_size_cmd(t_command cmd);

/**************** t_heredoc *****************/
void		init_heredoc(t_heredoc *heredocs);
t_heredoc	realloc_heredoc(t_heredoc heredocs, t_prg *prg);
void		add_heredoc(t_heredoc *heredocs, t_string new, int index,
				t_prg *prg);
t_string	get_heredoc(t_prg *prg, int expand, int i, int h_index);

/**************** custom ****************/
int			print_title(void);
int			biography(char *command);

/**************** Malloc  ****************/
void		*ft_malloc(t_prg *prg, size_t size);
int			ft_error_exit(t_prg *prg, int size, char *s1, ...);

/*************** MAIN ***************************/
int			ft_lstclear_all(t_list **lst, struct termios *old);

/**************** set_env ***********************/
void		set_signal(void);
int			initialization(char **envp, t_prg *prg);
int			set_export(char **envp, t_head_env *head, t_prg *prg);
char		*set_value_shlvl(int shlvl, t_string shlvl_var);

/**************** OPTIONAL ****************/
void		ft_free(char **str);
int			print_stderror(int error, int size, char *s1, ...);

/**************** Built in ********/
int			exec_builtin(char **command, t_head_env *head, t_prg *prg);
int			control_args(char *str);
int			print_export(t_head_env *head);
int			ft_export(t_head_env *head, char **command, t_prg *prg);
int			control_args(char *str);
int			ft_env(t_lst_env *lst, char **command);
int			ft_unset(t_head_env **head, char **command);
int			ft_echo(char **str);

int			ft_cd(char **str, t_head_env *head, t_prg *prg, t_string *pwd);
void		set_oldpwd_env(t_head_env *head, t_string *pwd, t_prg *prg);
void		set_new_pwd_env(t_head_env *head, t_string *pwd, t_prg *prg);
t_bool		set_new_path(char *str, t_string *path, t_prg *prg);
t_bool		set_home_env(t_string *path, t_lst_env *env, t_prg *prg);
t_bool		set_oldpwd(t_string *path, t_lst_env *env, t_prg *prg);
t_bool		set_home_getenv(char *str, t_string *path, t_prg *prg);
int			ft_pwd(t_string pwd);
int			print_export(t_head_env *head);
void		ft_exit(char **str, t_prg *prg);

/**************** Parsing ******************/
t_string	create_prompt(t_string pwd, t_prg *prg);
t_lst_cmd	*create_command(t_prg *prg);
void		split_wog(t_prg *prg, char c);
int			count_split_wog(const char *str, char charset);
t_bool		check_quotes(t_string cmd);
t_bool		check_pipes(t_command cmd);
t_bool		syntax_special_char(t_string *cmd, t_prg *prg);
t_bool		init_table_heredoc(t_prg *prg, int *save);
int			check_heredoc(char *str, int i, int *index);
void		find_arg_and_replace(t_prg *prg, int start, t_string *str);
void		pass_quotes(char *src, int *i, char c);

/**************** Exec_command *************/
int			exec_command(t_prg *prg);
int			get_redirections(t_prg *prg, t_lst_cmd *cmd);
char		**create_final_command(char **cmd, t_prg *prg);
void		ft_pipex(t_prg *prg, char **envp);
char		**trim_quotes_unneeded(char **cmd, t_prg *prg);
t_bool		is_builtin(t_prg *prg);
void		ft_exec_process(t_prg *prg, char **envp);
void		rm_heredocs_files(t_prg *prg, char **envp);
int			get_file_heredoc(t_string *file, t_prg *prg, int h_index);

/**************** Utils *************/
int			ft_double_dup(int fd1, int fd2, t_prg *prg);
int			ft_pipe(int *fd, t_prg *prg);
int			ft_close(int fd, t_prg *prg);
int			ft_dup2(int fd1, int fd2, t_prg *prg);
char		*ft_strdup_and_trim(char *src, int j, t_prg *prg);
int			ft_open(char *file, char *options, int *fd, t_prg *prg);

/**************** ARGS *************/
void		change_arg_command(t_prg *prg, t_string *str);
t_bool		is_arg(char *arg, int *start);

void		handler_forked(int signum);
void		handler_main(int signum);
void		handler_forked_sigquit(int signum);
void		handler_heredoc(int signum);

/************* PIPEX Utils **********/
void		ft_execve(char *cmd, char **args, char **envp, int *eacces);
void		ft_exec_path(t_prg *prg, char **envp, int *eacces);
t_bool		is_path(char *cmd);
t_bool		is_builtin(t_prg *prg);
void		set_signals(char *cmd);

/************ EXPORT Utils **********/
int			print_export(t_head_env *head);
int			ft_strchr_len(const char *s, int c);
t_bool		control_args(char *str);
void		add_elem_to_lst(char *arg, t_head_env *head, t_prg *prg);
void		replace_elem_of_lst(t_head_env *head, char *var, char *var_name,
				t_prg *prg);
void		init_env__(t_prg *prg);
void		try_path(t_prg *prg, t_lst_env *export, t_lst_env *env);

#endif