/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:39:10 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/11 09:46:11 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_creat_pipes(t_shell *shell, int k)
{
	int	i;

	i = 0;
	shell->pipes = malloc (k * sizeof(int *));
	if (!shell->pipes)
		return ;
	while (i < k)
	{
		shell->pipes[i] = malloc(2 * sizeof(int));
		i++;
	}
	if (k > 0)
		pipe(shell->pipes[0]);
}

void	ft_run_command(t_shell *shell, t_cmd *cmd)
{
	int	builtin;

	builtin = 0;
	builtin = ft_check_builtins(shell, cmd, 1);
	if (!builtin)
	{
		ft_get_cmd(shell, cmd->cmd);
		execve(shell->command_path, cmd->cmd, shell->env);
	}
}

void	first_c(t_cmd *cmd, t_shell *shell, int k)
{
	if (cmd->cmd[0] == NULL)
	{
		if (k > 0)
		{
			close(shell->pipes[0][0]);
			close(shell->pipes[0][1]);
		}
		if (cmd->infile != 0)
		{
			close(cmd->infile);
			close(cmd->outfile);
		}
		exit(0);
	}
	else if (k > 0)
		ft_first_cmd_help(shell, cmd);
	else if (cmd->infile != 0)
	{
		close(cmd->infile);
		close(cmd->outfile);
	}
	ft_run_command(shell, cmd);
	exit(0);
}

void	between_c(t_cmd	*cmd, t_shell *shell, int i)
{
	shell->id++;
	shell->prosess_id[shell->id] = fork();
	if (shell->prosess_id[shell->id] == -1)
	{
		printf("bash: fork: Resource temporarily unavailable\n");
		return ;
	}
	if (shell->prosess_id[shell->id] == 0)
	{
		ft_open_files(shell, cmd);
		if (shell->exit_creat == 1)
			exit (1);
		if (cmd->cmd[0] == NULL)
		{
			if (cmd->infile != 0)
			{
				close(cmd->infile);
				close(cmd->outfile);
			}
			exit(0);
		}
		ft_help_between_c(shell, cmd, i);
		ft_run_command(shell, cmd);
		exit(0);
	}
}

void	last_c(t_cmd *cmd, t_shell *shell, int i)
{
	if (cmd->cmd[0] == NULL)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		close(cmd->infile);
		close(cmd->outfile);
		exit(0);
	}
	close(shell->pipes[i][1]);
	if (cmd->infile != 0)
	{
		close(cmd->infile);
		close(cmd->outfile);
	}
	else if (shell->in == 0)
		dup2(shell->pipes[i][0], 0);
	close(shell->pipes[i][0]);
	close(shell->pipes[i][1]);
	ft_run_command(shell, cmd);
	exit(0);
}
