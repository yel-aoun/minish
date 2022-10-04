/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_help_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:22:52 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/02 12:28:09 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_infile(t_shell *shell, char *filename)
{
	int	i;

	i = 0;
	ft_check_access(filename, 2, shell);
	if (shell->exit_creat == 1)
		return ;
	ft_check_access(filename, 0, shell);
	if (shell->exit_creat == 1)
		return ;
	i = open(filename, O_RDWR, 0644);
	shell->in = 1;
	dup2(i, 0);
	g_glob[1] = 0;
}

void	ft_outfile(t_shell *shell, char *filename)
{
	int	i;

	i = 0;
	i = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	ft_check_access(filename, 2, shell);
	if (shell->exit_creat == 1)
		return ;
	ft_check_access(filename, 1, shell);
	if (shell->exit_creat == 1)
		return ;
	shell->out = 1;
	dup2(i, 1);
	g_glob[1] = 0;
}

void	ft_append(t_shell *shell, char *filename)
{
	int	i;

	i = 0;
	i = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
	ft_check_access(filename, 2, shell);
	if (shell->exit_creat == 1)
		return ;
	ft_check_access(filename, 1, shell);
	if (shell->exit_creat == 1)
		return ;
	shell->out = 1;
	dup2(i, 1);
	g_glob[1] = 0;
}

void	ft_open(int flags, char *filename, t_shell *shell)
{
	int	k;

	k = 0;
	if (flags == 1)
		ft_infile(shell, filename);
	else if (flags == 2)
		ft_outfile(shell, filename);
	else if (flags == 3)
		ft_append(shell, filename);
}

int	ft_check_exec_builtin(t_cmd *cmd)
{
	char	*cmp;
	int		k;

	k = 0;
	cmp = ft_strdup(cmd->cmd[0]);
	cmp = ft_lower(cmp);
	if (ft_strcmp(cmp, "echo") == 0)
		k = 1;
	else if (ft_strcmp(cmp, "env") == 0)
		k = 1;
	else if (ft_strcmp(cmp, "pwd") == 0)
		k = 1;
	else if (ft_strcmp (cmd->cmd[0], "exit") == 0)
		k = 1;
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		k = 1;
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		k = 1;
	else if (ft_strcmp (cmd->cmd[0], "unset") == 0)
		k = 1;
	free (cmp);
	return (k);
}
