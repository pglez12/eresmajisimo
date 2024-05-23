/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:39:59 by payllana          #+#    #+#             */
/*   Updated: 2024/05/23 11:42:11 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../src/libft/libft.h"
# include <limits.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <termios.h>

extern int	g_signal_flag;

# define TMP "/tmp/tmp_hd.tmp"

typedef struct s_fill_lst
{
	char	**cmds;
	char	**files;
	int		*red;
	char	**str;
	int		index;
}	t_fill_lst;

typedef enum e_tok_type
{
	INP,
	OUTP,
	APP,
	HEREDOC,
	PIPE,
	STR,
	ESP,
}	t_tok_type;

enum	e_value
{
	INPUT = 0,
	OUTPUT = 1,
	APPEND = 2,
	HD = 3,
};

typedef enum e_fd
{
	IN,
	OUT
}	t_fd;

typedef struct s_files
{
	int				red;
	char			*fname;
	struct s_files	*next;
}	t_files;

typedef struct s_envp
{
	char			*name;
	char			*content;
	struct s_envp	*next;
}	t_envp;

typedef struct s_cmd
{
	int				index;
	char			**cmd;
	t_files			*files;
	char			*infile;
	char			*outfile;
	int				type_in;
	int				type_out;
	char			*path;
	int				input_fd;
	int				output_fd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shellinfo
{
	char	**envp;
	t_envp	*env_lst;
	t_envp	*last_env;
	char	*path;
	t_cmd	*cmds;
	int		std_fd[2];
}	t_shellinfo;

typedef struct s_hd
{
	char	*str;
	int		fd;
	int		i;
	int		j;
	char	*del;
	char	*join;
}	t_hd;

typedef struct s_hd_u
{
	int		i;
	t_cmd	*tmp;
	t_files	*tmp_f;
}	t_hd_u;

typedef struct s_token
{
	char			*tk;
	struct s_token	*next;
}	t_token;

typedef struct s_fill_cmd
{
	t_shellinfo	*ms;
	int			err;
}	t_fill_cmd;

typedef struct s_parse_tok
{
	int			i;
	int			j;
	int			t;
	int			o;
	t_fill_lst	*fill;
}	t_parse_tok;

typedef struct s_dep_var
{
	char	*str;
	char	*tmp;
	char	*cnt;
	int		i;
	int		t;
	int		ini_var[4096];
	int		end_var[4096];
	int		t_var;
	int		c_var;
	int		rl_c;
}	t_dep_var;

typedef struct s_dep_var_remove
{
	char		*str;
	char		**split;
	int			t;
	char		*s;
	char		*n;
	t_dep_var	a;
}	t_dep_var_remove;

typedef struct s_auto_get_token
{
	int		i;
	int		est;
	int		est_next;
	int		est_tmp;
	char	*str;
}	t_auto_get_token;

typedef struct s_fds
{
	int		fdp[2];
	int		pipe_fd[2];
	int		pids[1000];
}	t_fds;

void		ft_exit_clean(t_shellinfo *mini, int err);
void		ft_err_msg(char *command, char *msg, char *cmd);
int			ft_check_redirs(t_cmd **cmd, int *pp_fd, int *r_pip, int *valret);
int			ft_redir_output(t_cmd *cmd, int *pipe_fd);
int			ft_export(char **cmd, t_shellinfo *mini, t_cmd *c);
int			ft_unset(char **cmd, t_shellinfo *mini, t_cmd *c);
void		ft_dup_pipes(int i, int fd[2], int fdp[2], t_cmd *cmds);
void		ft_dup_files(t_files *file);
int			ft_is_builtin(t_cmd *c);
int			ft_is_bin(t_cmd *c);
int			ft_check_file(t_cmd *cmd);
void		ft_exec_cmd(t_shellinfo *mini, t_cmd *cmds);

int			ft_exec_builtin(t_cmd *c, t_shellinfo *mini, int flag);
int			ft_builtin_infork(t_cmd *c, t_shellinfo *mini);

int			ft_is_var(char const *s);
void		anything_else_found(t_token **lst, t_auto_get_token *a,
				char const *s);
void		quotes_found(t_auto_get_token *a, char const *s, t_token **lst);
int			token_add_back(t_token **lst, char const *s, t_auto_get_token *a);
void		calc_states(t_auto_get_token *a, char const *s);
char		*get_content_var(t_envp *lst, char *name);
void		ft_util_dep_var1(int flag, t_dep_var *a, int err);
void		ft_util_dep_var2(int flag, t_dep_var *a, int next_is_quote);
void		ft_util_dep_var4(int flag, t_dep_var *a, t_envp *lst);
void		ft_util_dep_var3(int flag, t_dep_var *a);
void		ini_dep_var(t_dep_var *a, char const *s);
void		ft_get_files_files(t_parse_tok *a, char const **token,
				int err, t_envp *lst);
void		ft_get_cmd_files_str(t_parse_tok *a, char const **token, int err,
				t_envp *lst);
void		ini_fill_cmd_files(t_parse_tok *a, t_fill_lst *fill,
				char const **token);
void		ft_get_strs_cmd(t_parse_tok *a, char const **token,
				int err, t_envp *lst);
void		ini_fill_cmd(t_parse_tok *a, t_fill_lst *fill);
void		ft_err_msg(char *command, char *msg, char *cmd);
int			ft_check_redirs(t_cmd **cmd, int *pp_fd, int *r_pip, int *valret);
int			ft_redir_output(t_cmd *cmd, int *pipe_fd);
t_token		*ft_token_new(char *token);
void		ft_token_lst_addback(t_token **lst, t_token *node);
int			get_state(int x, int y);
int			get_alpha(int x, int y);
int			ft_automata(char *s, t_shellinfo *ms, int err);
int			ft_get_envp(char **envp, t_envp **list, unsigned int a);
t_envp		*ft_last_env(t_envp *lst);
void		ft_env_add_back(t_envp **lst, t_envp *new);
char		*ft_subenv(char *str, size_t ini, char del, size_t *n);
t_envp		*ft_append_node(char *var);
void		ft_sigint_handler(int sig);
void		ft_terminal(void);
void		ft_signals(void);
int			ft_execute(t_shellinfo *mini);
int			ft_redir_input(t_cmd *cmd, int last_pipe);
void		ft_dup2(int fd, int std);
int			ft_open(t_cmd *cmd, int in_out);
int			ft_count_files(t_files *fil, int	*infd, int *outfd, int *hdfd);
void		ft_fill_red(int red_type, t_cmd *cmd, char *filename);
void		ft_handle_lst(t_files *fil, int infd, int outfd, t_cmd *cmd);
int			ft_check_files(t_cmd **cmd);
void		ft_check_access(int red_type, char *filename);
int			ft_exect_builtin(t_cmd *cmds, t_shellinfo *mini);
int			ft_execve(t_cmd *cmds, t_shellinfo *mini, int *pipe_fd);
char		*ft_check_path(t_cmd *cmd, t_shellinfo *mini);
int			ft_echo(char **args);
int			ft_exit(t_cmd *cmd, t_shellinfo *mini);
int			ft_env(t_envp *lst, int flag);
int			ft_pwd(t_shellinfo *mini);
int			ft_cd(char **cmd, t_shellinfo *mini, t_cmd *c);
int			ft_work_cd(char **cmd, t_shellinfo *mini);
void		ft_change_node_help(t_envp **lst, char *name, char *content);
int			ft_not_digit(char *cmd, int i);
t_envp		*ft_new_node(char *name, char *content);
int			ft_valid(char *str);
void		ft_sort_env(t_shellinfo *mini);
void		ft_free_grid(char **array);
void		ft_free_file_lst(t_files **files);
void		ft_free_envp(t_envp **lst);
void		ft_free_cmd_lst(t_cmd **cmd);
void		ft_free_mini(t_shellinfo *mini);
void		ft_free_all(t_shellinfo *mini);
char		*ft_strdup_len(char const *s, int len);
char		*ft_join(char *s1, char *s2);
void		heredoc(t_shellinfo lst);
void		ft_fill_lst(char const *s, t_shellinfo *ms, int err);
t_cmd		*ft_cmdnew(t_fill_lst *fill);
void		ft_cmd_addback(t_cmd **lst, t_cmd *node);
void		ft_fill_file_lst(t_files **lst, char **files, int *red);
void		ft_token_lst_addback(t_token **lst, t_token *node);
char		*ft_join_char(char *s, char c);
int			automata_find_char(char c);
void		automata_get_token(char const *s, t_token **lst);
void		ft_clear_token_lst(t_token **lst);
t_tok_type	ft_get_token(char const *token);
int			ft_strdouble_len(char **s);
char		**ft_strdouble_dup(char **s);
char		**ft_strdouble_add(char **s, char *add);
char		**dep_var_remove_quotes(char const *s,
				char const *next, int err, t_envp *lst);
char		**ft_split_moded(char const *s, char c);
char		*dep_var_remove_quotes1(char const *s,
				char const *next, int err, t_envp *lst);
int			red_type(t_tok_type red);
int			count_red(char const **s);
void		free_double_char(char ***s);
void		reset_fill(t_fill_lst *fill, char ***tok);
void		ft_fill_ini(t_fill_lst *fill);
int			ft_is_quote(char const *s);
int			ft_is_quote_files(char const *s);
char		*ft_del_single_quote(char *s);
char		*ft_del_single_quote_files(char *s);
char		*ft_del_double_qoute(char *s);
char		*ft_del_double_qoute_files(char *s);
char		*ft_rem_quote(char *s, int quote_type, t_dep_var *a);
char		*ft_rem_quote_files(char *s, int quote_type);
#endif
