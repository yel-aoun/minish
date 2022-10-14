/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:52:47 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/12 15:50:17 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ex_betw(t_shell *shell, t_cmd *command, int k)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = command;
	cmd = cmd->next;
	while (i < k - 1)
	{
		pipe(shell->pipes[i + 1]);
		between_c(cmd, shell, i);
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
		cmd = cmd->next;
	}
}

void	ft_wait_childs(t_shell *shell, int k)
{
	int	i;
	int	stat;

	i = 0;
	stat = 0;
	while (i < k)
	{
		waitpid(shell->prosess_id[i], &stat, 0);
		if (WIFEXITED(stat))
			g_glob[1] = WEXITSTATUS(stat);
		if (stat == 2)
			g_glob[1] = 130;
		if (stat == 3)
			g_glob[1] = 131;
		i++;
	}
}

void	ft_help_exec_cmd(t_shell *shell, t_cmd *command, int k)
{
	t_cmd	*cmd;

	cmd = command;
	if (k > 0)
	{
		ex_betw(shell, cmd, k);
		shell->id++;
		shell->prosess_id[shell->id] = fork();
		if (shell->prosess_id[shell->id] == 0)
		{
			while (cmd->next)
				cmd = cmd->next;
			ft_open_files(shell, cmd);
			if (shell->exit_creat == 0)
				last_c(cmd, shell, k - 1);
			else
				exit(0);
		}
		else
		{
			cmd = command;
			ft_close(shell, k);
			ft_close_files(cmd);
		}
	}
}

void	execute_cmds(t_cmd *command, t_shell *shell, int k)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = command;
	shell->id = 0;
	shell->prosess_id = malloc(sizeof(int) * (k + 1));
	if (!shell->prosess_id)
		return ;
	signal(SIGINT, ft_sig_child);
	shell->prosess_id[shell->id] = fork();
	if (shell->prosess_id[shell->id] == -1)
		return ;
	if (shell->prosess_id[shell->id] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		ft_simpl_help_in_exec(shell, cmd, k);
	}
	else
		ft_help_exec_cmd(shell, cmd, k);
	ft_wait_childs(shell, (k + 1));
	free(shell->prosess_id);
}

void	exec(t_shell *shell, t_cmd *cmd)
{
	int	k;
	int	l;
	int	open;

	l = 0;
	open = 0;
	k = co_unt(cmd);
	if (k == 0)
	{
		open = ft_check_exec_builtin(cmd);
		if (open)
			ft_open_files(shell, cmd);
		l = ft_check_builtins(shell, cmd, 0);
		if (l == 0)
			execute_cmds(cmd, shell, k);
	}
	else
	{
		ft_creat_pipes(shell, k);
		execute_cmds(cmd, shell, k);
		ft_free_pipes(shell->pipes, k);
	}
}
