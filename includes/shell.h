/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:36:08 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/24 11:28:07 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include<stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <string.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../get_next/get_next_line.h"
# include "minishell.h"

# define GREEN "\033[0;32m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"
typedef struct sh
{
	int	i;
	int	j;
	int	k;
	int	l;
}			t_sh;

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
	int		i;
	int		k;
	int		exit_status;
}			t_shell;

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

//src/ft_init.c
void	ft_init_env(t_shell *shell, char **new);
int	ft_check_builtins(t_shell *shell, t_cmd *command);

void    ft_get_exec(t_shell *shell, t_cmd *cmd);

//builtins
int		ft_cd(t_shell *shell, t_cmd *cmd);
int		ft_echo(t_cmd *cmd);
int		ft_put_env(t_shell *shell);
int		ft_put_export(t_shell *shell, char *str);
int		ft_put_pwd(void);
int		ft_unset(t_shell *shell, t_cmd *cmd);
int		ft_exit(t_shell *shell, t_cmd *cmd);

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
void	ft_up_help(t_shell *shell, char *str);

void	exec(t_shell *shell, t_cmd *cmd);


// get_next_line.c
// char	*get_next_line(int fd);
// char	*ft_save_what_i_did_read(int fd, char *save_read);
// char	*ft_static(char *save);
// char	*ft_put(char *s_r);
// char	*ft_strdup_demo(char *s1, int d);
// char	*ft_strjoin_t(char	*s1, char	*s2);
// char	*ft_strjoin_ft(char *s1, char *s2, int s);

#endif