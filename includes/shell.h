/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:36:08 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/04 18:34:12 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include<stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <string.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "minishell.h"

# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"

typedef struct shell
{
	char	**export;
	char	**env;
	int		argc;
	char	**argv;
	char	**cmd_args;
	int		**pipes;
	int		**pip_herdoc;
	char	**command;
	char	*command_path;
	char	**path;
	char	*pwd;
	int		err;
	int		*prosess_id;
	int		id;
	int		i;
	int		k;
	int		in;
	int		out;
	int		h_c;
	int		exit_status;
	int		exit_creat;
	int		t_sig_c;
}			t_shell;

int	g_glob[2];

//utiles/ft_tools.c
int		ft_strcmp(char *s1, char *s2);
char	**ft_add_env(t_shell *shell, char **env, char *str);
char	**ft_add_export(t_shell *shell, char **env, char *str);

//utiles/utiles_1.c

int		ft_count(char **env);
char	*ft_find_in_env(char **new, char *find);
void	ft_export(t_shell *shell, char **env);
void	ft_env(t_shell *shell, char **env);

//utiles/utiles_2.c
char	**ft_pwd(char **new);
char	**ft_oldpwd(char **new);
int		ft_is_n(char *str);

//src
void	ft_init_env(t_shell *shell, char **new);
int		ft_check_builtins(t_shell *shell, t_cmd *command, int p);
char	*ft_lower(char *str);

void	ft_get_exec(t_shell *shell, t_cmd *cmd);

//builtins
int		ft_cd(t_shell *shell, t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_put_env(t_shell *shell, t_cmd *cmd);
int		ft_put_export(t_shell *shell, t_cmd *cmd);
int		ft_put_pwd(t_shell *shell);
int		ft_unset(t_shell *shell, t_cmd *cmd);
void	ft_exit(t_cmd *cmd, int p);

//builtins/unset_help.c
void    ft_valide_unset(t_shell *shell, t_cmd *cmd, int i);
int	ft_valid_unset(char *str);

//builtins/export.c
int		ft_search(char *str, char c);
int		ft_valid_name(char	*s);

//src/update.c

// void	ft_unset(t_shell *shell, char *str);
char	**update_env(t_shell *shell, char *str);
char	**update_export(t_shell *shell, char *str);

//utiles/ft_up.c

char	**ft_up_env(t_shell *shell, char *str);
char	**ft_up_export(t_shell *shell, char *str);
char	**ft_join_export(t_shell *shell, char *str);
char	**ft_join_env(t_shell *shell, char *str);

//utiles/ft_tools_help.c
char	**ft_add_export_help1(t_shell *shell, \
		char *splt, char **env, char *str);
char	**ft_add_export_help2(char **env, char *str);
char	**ft_add_env_help(char **env, char *str);
char	*ft_add(char *str);
int		ft_is_longer(char *str, char *str1);

// exec/exec_utiles.c
void	ft_get_cmd(t_shell *shell, char **cmd);

// exec/exec_tools.c
void	ft_err_cmd(char *str, int k);
void	ft_error(char *str);

//exec/exec_cmd.c
void	ft_creat_pipes(t_shell *shell, int k);
void	first_c(t_cmd *cmd, t_shell *shell, int k);
void	between_c(t_cmd	*cmd, t_shell *shell, int i);
void	last_c(t_cmd *cmd, t_shell *shell, int i);

//builtins/ft_help_export.c
int		ft_write(char *str);
void	ft_up_help(t_shell *shell, t_cmd *cmd);

void	exec(t_shell *shell, t_cmd *cmd);

//src/ft_exec.c
void	ft_check_her_doc(t_shell *shell, t_cmd *command);
void	ft_create_pipes_heredoc(t_shell *shell, int k);
int		ft_count_herdoc_pipes(t_cmd *command);

void	ft_open_files(t_shell *shell, t_cmd *command);

//signals//main.c
void	ft_sig_int(int sig);

//exec/exec_cmd_help.c
void	ft_first_cmd_help(t_shell *shell, t_cmd *cmd);
void	ft_help_between_c(t_shell *shell, t_cmd *cmd, int i);

//exec/execution_help.c
void	ft_close(t_shell *shell, int k);
int		co_unt(t_cmd *cmd);
void	ft_close_files(t_cmd *command);

//exec/execution_help2.c
void	ft_open(int flags, char *filename, t_shell *shell);
void	ft_append(t_shell *shell, char *filename);
void	ft_outfile(t_shell *shell, char *filename);
void	ft_infile(t_shell *shell, char *filename);
int		ft_check_exec_builtin(t_cmd *cmd);

//exec/ft_check_access.c
void	ft_check_access(char *arg, int n, t_shell *shell);
void	ft_help_check_access(char *arg, t_shell *shell);
void	ft_help_print_err_fille(char *err);

void	ft_exit_sig(char *str);

#endif