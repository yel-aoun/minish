/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:39:10 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/29 18:17:54 by yel-aoun         ###   ########.fr       */
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

void	first_c(t_cmd *cmd, t_shell *shell, int k)
{
	int	builtin;
	builtin = 0;
	if (cmd->cmd[0] == NULL)
	{
		if (k > 0)
		{
			close(shell->pipes[0][0]);
			close(shell->pipes[0][1]);
		}
		if(cmd->infile != 0)
		{
			close(cmd->infile);
			close(cmd->outfile);
		}
		exit(0);
	}
	else if (k > 0)
	{
		close(shell->pipes[0][0]);
		if (cmd->infile != 0)
		{
			close (cmd->infile);
			close(cmd->outfile);
		}
		if (shell->out == 0)
			dup2(shell->pipes[0][1], 1);
		close(shell->pipes[0][0]);
		close(shell->pipes[0][1]);
	}
	else if(cmd->infile != 0)
	{
		close(cmd->infile);
		close(cmd->outfile);
	}
	builtin = ft_check_builtins(shell, cmd, 1);
	if (!builtin)
	{
		ft_get_cmd(shell, cmd->cmd);
		execve(shell->command_path, cmd->cmd, shell->env);
	}
	exit(0);
	// perror("");
}

void	between_c(t_cmd	*cmd, t_shell *shell, int i)
{
	int		builtin;

	shell->id++;
	shell->prosess_id[shell->id] = fork();
	builtin = 0;
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
			if(cmd->infile != 0)
			{
				close(cmd->infile);
				close(cmd->outfile);
			}
			exit(0);
		}
		close(shell->pipes[i][1]);
		close(shell->pipes[i + 1][0]);
		if (cmd->infile != 0)
		{
			close(cmd->infile);
			close(cmd->outfile);
		}
		else if (shell->in == 0)
			dup2(shell->pipes[i][0], 0);
		if (shell->out == 0)
			dup2(shell->pipes[i + 1][1], 1);
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		close(shell->pipes[i + 1][0]);
		close(shell->pipes[i + 1][1]);
		builtin = ft_check_builtins(shell, cmd, 1);
		if (!builtin)
		{
			ft_get_cmd(shell, cmd->cmd);
			execve(shell->command_path, cmd->cmd, shell->env);
		}
		exit(0);
	}
}

void	last_c(t_cmd *cmd, t_shell *shell, int i)
{
	int	builtin;

	builtin = 0;
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
	builtin = ft_check_builtins(shell, cmd, 1);
	if (!builtin)
	{
		ft_get_cmd(shell, cmd->cmd);
		execve(shell->command_path, cmd->cmd, shell->env); 
	}
	exit(0);
	// perror("");
}
