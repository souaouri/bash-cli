/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:35:32 by souaouri          #+#    #+#             */
/*   Updated: 2024/05/17 00:35:32 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>

# define SYNTAX_ERROR			"syntax error near unexpected token `newline'"
# define INPUT_ERROR			"Please Enter Valid Argument\n"
# define ERROR_IN_ALLOCATION	"Error In Allocation"
# define SINGLE_QUOTE			'\'' 
# define DOUBLE_QUOTE			'\"' 
# define AMBIGUOUS_REDIRECT "ambiguous redirect"

typedef struct s_addresses
{
	void					*content;
	struct s_addresses		*next;
}					t_addresses;

typedef struct s_util
{
	int	i;
	int	check;
	int	len;
	int	hold;
}		t_util;

typedef struct s_var
{
	int		exit_status;
	int		hold_fd_in;
	int		pid;
	int		p_in ;
	int		p_out;
	int		i;
	int		check;
	t_util	*util;
}		t_var;

typedef enum s_token
{
	word,
	mpipe,
	redirect_in,
	redirect_out,
	append_out,
	heredoc,
	redirect_app,
	delimiter,
	file,
}	t_token;

typedef enum wquotes
{
	doubleQuotes,
	singleQuotes,
}	t_wquotes;

typedef struct s_lexer
{
	char			*str;
	t_token			token;
	int				i;
	int				expanded;
	t_wquotes		wquotes;
	struct s_lexer	*next;
	struct s_lexer	*prev;
	int				has_q;
}					t_lexer;

typedef struct s_simple_cmds
{
	char					*cmd;
	char					**args;
	char					**cmmd;
	int						in_file;
	int						out_file;
	int						aout_file;
	int						heredoc;
	int						stop_ex;
	int						is_ambugious;
	int						is_error;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}							t_cmds;

typedef struct env
{
	char		*content;
	struct env	*next;
}			t_env;

typedef struct tools
{
	char	*pwd;
	char	*old_pwd;
}			t_tools;

typedef struct env_test
{
	char	**res;
	t_env	**env;
}			t_en_test;

typedef struct int_t
{
	int	i;
	int	j;
}		t_int;

int		open_files_in(t_lexer **lexer, t_token token, \
	t_cmds **cmds, t_env **env);
void	sighandler(int sig);

//libift func
char	*ft_strncpy(char *s, int len);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
void	ft_putstr_fd(char *str, int fd);

//lexer_list
t_lexer	*ft_lstlast(t_lexer *lexer);
t_lexer	*ft_lstnew(int content);
int		ft_lstsize(t_lexer *lst);
void	ft_lstadd_back(t_lexer **lexer, t_lexer *new);
void	ft_lst_remove(t_lexer **lexer, int index);

//signals
void	sighandler(int sig);

//main
int		handel_quotes(char *line);
void	notify_signals(void);

//remove quotes
void	remove_quotes(t_lexer **lexer);

//quotes_spaces
void	*add_spaces(char *line);

//tokenizer
void	tokenizer(char **res, t_lexer **lexer);

//utils_string
size_t	ft_strlen(const char *s);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char *s);

//utils_free
void	allocation_error(char *s);
void	error_msg(char *s, t_env **env_list);
void	free_lexer(t_lexer *lexer);

//utils_quotes_spaces
void	set_redir(char *s, int *j, int *i, char c);
int		is_redir_has_found(char c);
int		handel_quotes(char *line);
int		quotes(char *line, char q);

//my split
char	**my_split(char const *s, char c);

//syntax error
int		syntax_error(t_lexer **lexer, t_env **env);
void	handel_herdoc_err(t_lexer **lexer, t_cmds **cmds, t_env **env);

// utils_split
char	*ft_word(char *s, char **arr, char ind, char quotes);
void	wait_till_end(char **s);
void	count_if_char(char *s, int *i);

//parser
t_cmds	*ft_lstnew_cmd(void);
int		ft_lstsize_cmd(t_cmds *lst);
void	ft_lstadd_back_cmd(t_cmds **cmds, t_cmds *new);
t_cmds	*ft_lstlast_cmd(t_cmds *cmds);
int		handel_if_file(t_lexer ***lexer, int fd);
int		handel_files(t_lexer **tmp, t_cmds *cmds, t_env **env);
int		get_lcmd(t_lexer *lexer);
int		open_files(t_lexer **lexer, t_token token, t_cmds **cmd, t_env **env);
int		save_heredoc(t_lexer **lexer, t_cmds **cmds, t_env **env);
void	save_heredoc2(t_lexer **lexer);
void	modify_exit_status(int nbr, t_env **env_list);
void	init_arrays(t_cmds *cmds);
void	*parser(t_lexer **lexer, t_cmds **cmds, int len, t_env **env);
int		handel_heredoc(char *del, t_cmds **cmds, t_env **env);

//expand heredoc
char	*expanding_str_here(char *s, t_env **env);
int		handel_ctr(int fd_in, t_cmds **cmds);
//expanding

void	handel_expanding(t_lexer **lexer, t_env **env_list);
char	*expand_str(char *s, t_env **env_list);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		str_chr(char *s, char c);
char	*ft_strdup(const char *s1);
char	*handel_double_q(char *result, char *s, t_int *sin_t, t_env **env_list);
char	*handel_singleq(char *result, char *s, int *i, int *j);
char	*al_exp(char *str, int *pos, t_env **env_list);
int		get_len_ep(char *s);
int		end_of_proccessing(char *s, int i);
int		is_real_char(char *s, int i);
char	*expanding_str(t_lexer **tmp, t_env **env_list);

//expand utils
void	expanding_cases(t_lexer **tmp, t_env **env_list);
void	*find_dollar(char *result, char *s, int *i);
char	*m_get_env(char *str, t_env **env_list);
int		check_if_noexpand(t_lexer **tmp);
int		init_expand(char *s, int *i, int *cnt);
char	*handel_other_cases(char *s, char **result, int *i, t_env **env);
int		is_q_withspaces(char c);
char	*handel_ex_q(t_int *is, t_lexer **t, char **res, t_env **env);
t_int	*init_ints(void);

//debugging
void	print_cmd(t_cmds **cmds);
void	printf_str(char *s);
void	printf_int(int d);
void	print_lexer(t_lexer *lexer);

//execution
void	ft_fork(char *nood, t_env *list_env);
int		ft_strlen_1(char **ptr);
void	echo(char **cmd, t_cmds *cmds);
void	execut_cmd(t_env **list_env, char **nood, t_cmds *cmds);
void	ft_exec(char **cmd, char **env);
void	*free_double_ptr(char	**ptr);
void	child(char *nood, char **env);
void	parent(char *nood, char **env);
char	**ft_split_exe(char *s, char c);

//utils
int		no_quotes(char *line, int i);
int		has_q(char *s);
int		is_quotes(char c);
int		is_withspaces(char c);
int		is_redirs(t_lexer *lexer);
int		is_number(char c);

// // virtual
void	ft_check(char *cmd, char **env);
char	*ft_strchr(char *s, int c);
char	*ft_find_path(char **env, char *var, int j);
void	ft_find_pwd(t_env *list_env);
t_env	*get_env(char **env);
void	get_cd(char *cmd);
int		export_exe(char **cmd, t_env *list_env);
void	write_env(t_env *env);
char	**change_list_to_env(t_env *list_env);
int		ft_lstsize_env(t_env *lst);
void	multiple_cmd(t_env **env_list, t_cmds *list, int len);
t_env	*ft_lstnew_env(char *line);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	change_list(t_cmds *list);
void	initialize_files(t_cmds	**list);
char	**join_cmd_arg(char *cmd, char **arg);
void	add_emergency_env(t_env **env);
int		unset(t_env **list_env, char *arg);
char	*get_env_eq(char *new);

// export
char	*ft_itoa(int n); ////
char	*add_double_quotes(char *var);
void	ft_sort_env(t_env *env);
char	*get_var_from_beg_to_eq(char *var);
char	*get_eq_to_fin(char *var);
int		check_var_does_it_exist(char *arg, t_env *list_env);
int		check_arg_is_valide(char *arg);
int		check_for_first_char(char *arg);
char	*get_env_eq(char *new);
char	*find_var(t_env *list_env, char	*var);
t_env	*env_dup(t_env *list);
int		check_for_plus_and_eq(char *arg, int w);
char	*remove_plus(char *new);
void	add_variable(t_env *list_env, char *new, int error);
int		exit_builtins(t_cmds *cmd, char **args, int len, t_env *list_env);
int		print_error(char *cmd, char *type);
int		cd_exec(t_cmds *cmds, t_env *list_env);

// void	*my_alloc(size_t size);
void    *my_alloc(size_t size, int free);
int		builtins_print_error(char *cmd, char *type);
char	*change_path_cd(t_tools *tools);

//src
void	multiple_cmd_util_0(t_var **v, t_cmds *list, t_env **e_l, int l);
void	multiple_cmd_util_1(int in_file, int *hold_fd_in);
void	multiple_cmd_util_2(int *hold_fd_in);
void	multiple_cmd_util_3(t_cmds *list, int *hold_fd_in);
void	multiple_cmd_util_4(t_cmds *list);
int		print_error(char *cmd, char *type);
int		check_is_biltus(char *cmd);
int		run_built(t_env **list_env, char **nood, t_cmds *cmds, int len);
void	multiple_cmd_util_5(t_cmds *list, int p_in, int p_out);
void	reducing(t_cmds *list, int *hold_fd_in);
int		initialize_var(t_var **var, t_cmds *list);
void	multiple_cmd_util_7(t_var **var, t_cmds **list, int len);
int		check_is_dir(char *cmd);
int		ft_strncmp_file(const char *s1, const char *s2, unsigned int n);
int		ambugious(t_cmds **list);
void	execut(t_var *var, t_env **env_list, t_cmds *list);
int		run_bui_p(t_env **list_env, char **nood, t_cmds *cmds, int len);
int		ft_atoi(const char	*str);
int		check_var(char	*cmd, t_env *list_env);
int		if_var_exist_return(char *cmd, t_env *list_env);
void	add_path_to_env(t_tools *tools, t_env *list_env);
void	exec_if_path_eq_null(char **cmd, char **env);

//builtins
int		check_to_print_exit(int len);
int		check_for_errors(char *arg, int i, int *error);
int		_remove_var(t_env *temp, char *new);
int		preparing_var(t_env *list_env, char *new);
void	add_variable(t_env *list_env, char *new, int error);
void	is_error(char *cmd);
int		ft_isdigit(int c);
void	cd_error(void);
int		check_for_arg_cd(char *cmd);
char	*to_lowercase(char *str);
char	*extract_exit_status(t_env *env_list);
void	add_emergency_pwd(t_tools *tools, t_env *list_env);
void	set_pwd(t_tools *tools, t_env *list_env);
int		chdir_func(t_cmds *s_cmd, t_tools *tools, t_env *list_env);
void	exit_with_exit_status(t_cmds *cmd, char **args);
int		get_exit_code(char *arg, int *error);

#endif
// #endif
