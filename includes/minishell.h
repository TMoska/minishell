/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 16:57:49 by moska             #+#    #+#             */
/*   Updated: 2017/03/28 14:40:17 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <sys/stat.h>
# include <term.h>
# include <curses.h>
# include <termios.h>
# include <termcap.h>
# include <sys/wait.h>
# include <fcntl.h>

# define BUFF_SIZE 1024

/*
**	Button Key codes
*/

# define BTN_DEL	2117294875
# define BTN_BACK	127

# define BTN_HOME	4741915
# define BTN_END	4610843

# define BTN_ALEFT	1146821403
# define BTN_ARIGHT	1130044187

# define BTN_LEFT	4479771
# define BTN_RIGHT	4414235
# define BTN_UP		4283163
# define BTN_DOWN	4348699

# define BTN_ESC	27
# define BTN_ENTER	10
# define BTN_TAB	9
# define BTN_CTRL_D	4

# define BTN_CTRL_P 16
# define BTN_CTRL_I 9
# define BTN_CTRL_K 11
# define BTN_CTRL_L	12

/*
**	Termcaps commands
*/

# define MOVE_LEFT	ft_putstr(tgetstr("le", NULL));
# define MOVE_RIGHT	ft_putstr(tgetstr("nd", NULL));

# define DEL		ft_putstr(tgetstr("dc", NULL));
# define CURS_LEFT	ft_putstr(tgetstr("cr", NULL));
# define DEL_LINE	ft_putstr(tgetstr("ce", NULL));

/*
**	Types and Structs
*/

extern int g_exit_code;

typedef struct		s_envl
{
	struct s_envl	*next;
	char			*name;
	char			*value;
}					t_envl;

typedef struct		s_quotes
{
	t_bool			was_quoted;
	t_bool			dquote;
	t_bool			squote;
	t_bool			bquote;
	t_bool			escape;
	t_bool			oneline;
}					t_quotes;

typedef struct		s_h_lst
{
	char			*cmd;
	int				index;
	struct s_h_lst	*next;
	struct s_h_lst	*prev;
}					t_h_lst;

typedef struct		s_hist
{
	int				size;
	int				at_index;
	struct s_h_lst	*list;
}					t_hist;

typedef struct		s_shell
{
	char			*buff;
	t_list			*commands;
	char			**cmd;
	int				cmd_len;
	int				ret;
	int				exit;
	char			**env;
	t_envl			*env_list;
	struct termios	term;
	int				tc_ok;
	int				tc_in;
	int				tc_len;
	int				prompt_len;
	t_hist			*history;
	char			*clipboard;
	char			*tmp_buff;
	t_quotes		*q;
	struct s_tkn	*tkns;
	struct s_tkn	*tree;
	int				token_count;
	t_list			*heredoc;
}					t_shell;

typedef struct		s_tkn
{
	char			*data;
	int				type;
	struct s_tkn	*left;
	struct s_tkn	*right;
}					t_tkn;

typedef struct		s_env_s
{
	int				set;
	int				unset;
	int				ignore;
	int				cmd;
	int				null;
}					t_env_s;

/*
**	Core function prototypes
*/

void				print_prompt(t_shell **shell, char *prompt);
char				*get_git_branch(void);
void				build_prompt(t_shell **shell);
t_shell				*get_shell(char **env);
int					validate_and_prep_cmd(t_shell **shell);
int					interpret_line(char *cmd);
char				*loop_through_paths(char ***paths, int *i, char *cmd);
int					command_not_found(t_shell **shell);
int					permission_denied(t_shell **shell, t_bool name, char *path);
int					must_exec(t_shell **shell, char *exec, char **ptr,\
					char **env);
void				print_env(t_envl *env_list);
t_envl				*built_env_list(char **env);
void				no_file_or_dir(t_shell **shell, t_bool name);
void				not_a_dir(t_shell **shell);
void				sig_callback(int s_num);

/*
**	Cleaning
*/

void				clean_shell(t_shell **shell);
void				mid_clean_shell(t_shell **shell);
void				clean_btree(t_tkn *tree);
void				del_lst_str(void **content, size_t *content_size);

/*
**	Environment list custom struct & functions
*/

void				envladd(t_envl **begin_list, t_envl *new);
t_envl				*envlnew(char *name, char *value);
int					envladd_back(t_envl **begin_list, t_envl *new);
char				*get_env_val(t_shell **shell, char *name);
void				clean_env_list(t_envl **begin_list);
int					env_lst_size(t_envl *begin_list);
void				rebuild_str2env(t_shell **shell);

/*
**	Builtins
*/

int					try_a_builtin(t_shell **shell, char *base_cmd,\
					char *full_cmd);
int					builtin_exit(t_shell **shell);
int					builtin_env(t_shell **shell);
int					builtin_getenv (t_shell **shell);
int					builtin_setenv(t_shell **shell);
int					builtin_unsetenv(t_shell **shell);
int					builtin_cd(t_shell **shell);
int					op_null(char **cmd);
int					op_unset(char **cmd);
int					op_setenv(char **cmd);
int					op_ignore(char **cmd);
int					op_cmd(char **cmd);
int					is_setenv(char *a);
int					is_null(char *a);
int					is_ignore(char *a);
char				**build_tmp_environment(char **cmd);
void				print_setenv(char **cmd);
void				work_as_newenv(char **cmd, t_shell **shell);
void				work_with_alterenv(char **cmd, t_shell **shell);
void				work_environ_and_display(char **cmd, t_shell **shell);
void				do_setenv(t_shell **shell, char *name, char *value);
void				change_symlink_directory(t_shell **shell, char *path);
int					prep_and_change(t_shell **shell);
int					builtin_echo(t_shell **shell, char *cmd);
void				join_back(char ***split_tab, char **new, int *size, int *i);
void				builtin_export(t_shell **shell);

/*
**	Reading
*/

void				read_input(t_shell **shell, char *heredoc);
void				work_buffer(t_shell **shell, char *buffer);
int					reset_line(t_shell **shell);

/*
**	Heredoc
*/

void				scan_heredocs(t_shell **shell);

/*
**	Terminall
*/

int					term_init(t_shell **shell);
int					term_trigger(t_shell **shell, int off);
void				move_cursor_sides(t_shell **shell, unsigned int key);
void				move_cursor_alt(t_shell **shell, unsigned int key);
void				modify_buffer(t_shell **shell, unsigned int key);
void				clean_buffer(t_shell **shell);
void				cut_line(t_shell **shell, unsigned int key);
void				clean_input(t_shell **shell);
void				paste(t_shell **shell);
void				copy(t_shell **shell);
int					clean_terminal(void);

/*
**	History
*/

void				hist_add(t_shell **shell);
void				history(t_shell **shell, unsigned int key);
int					print_history(t_shell **shell);
char				*history_search_first_match(t_shell **shell, char *s);
int					replace_double_exclamation(t_shell **shell, char *tmp);
int					replace_single_exclamation(char **cmd);
void				replace_ation(t_shell **shell, char *cmd);
void				set_hist_of_index(t_shell **shell, int index);
t_h_lst				*hist_at_index(t_shell **shell, int index);
int					no_history_err(char *arg);
char				*history_search_first_arg_match(t_shell **shell, char *s);
int					single_excl_type(char *str);

/*
**	Quotes
*/

int					do_quotes(t_shell **shell);

/*
**	Tokenizing
*/

t_tkn				*tkn_new(char *data, int type);
int					tkn_new_to_back(t_tkn **lst, char *data, int type);
char				**split_command(char *cmd);
int					if_op_find_priority(char *s);
int					tokenize(t_shell **shell);
int					get_tokens(t_shell **shell, int first);
void				tkn_move_args_to_start(t_tkn **dst, t_tkn **src);
void				reorganize_tokens(t_shell **shell);
void				move_pointers(t_tkn *init, t_tkn **start, t_tkn **ptr1, \
					t_tkn **ptr2);
void				arrange_nodes_in_priority(t_shell **shell);
void				syn_error(void);
t_tkn				*build_tree(t_tkn *tree);
int					in_range(int i, int start, int end);
void				add_cmds(char ***cmds, char *cmd, int *offset, int *len);
int					is_op(char *c);
void				add_command(char ***cmds, char *cmd, int *offset, int *len);
t_tkn				*tkn_pre_last(t_tkn *lst);
t_tkn				*tkn_search_node(t_tkn *node, char *data);
t_tkn				*tkn_last(t_tkn *node);

/*
**	Execution
*/

int					test_n_execute(t_shell **shell, char *exec, char **ptr, \
					char **env);
int					execute_node(t_tkn *node);
int					execute_right_redirection(t_tkn *node);
int					execute_logic_operators(t_tkn *node);
int					execute_semicolon(t_tkn *node);
int					execute_left_redirection(t_tkn *node);
int					execute_pipe(t_tkn *node);
int					execute_fd_aggregation(t_tkn *node);
int					get_and_test_executable(t_shell **shell, char **exec);
int					open_tmp_heredoc(int *fd);
int					redirection_type(t_tkn *node);
int					execute_two_left(t_tkn *node, char *out);
int					fork_error(void);


void				print_tokens(t_tkn *tokens);

#endif
