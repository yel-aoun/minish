/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:39:10 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/24 11:25:18 by yel-aoun         ###   ########.fr       */
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
	if (k > 0)
	{
		close(shell->pipes[0][0]);
		dup2(shell->pipes[0][1], 1);
		close(shell->pipes[0][0]);
		close(shell->pipes[0][1]);
	}
	builtin = ft_check_builtins(shell, cmd);
	if (!builtin)
	{
		ft_get_cmd(shell, cmd->cmd);
		execve(shell->command_path, cmd->cmd, shell->env);
	}
	// perror("");
}

void	between_c(t_cmd	*cmd, t_shell *shell, int i)
{
	pid_t	pid;
	int		builtin;

	pid = fork();
	builtin = 0;
	if (pid == -1)
	{
		printf("bash: fork: Resource temporarily unavailable\n");
		return ;
	}
	if (pid == 0)
	{
		close(shell->pipes[i][1]);
		close(shell->pipes[i + 1][0]);
		dup2(shell->pipes[i][0], 0);
		dup2(shell->pipes[i + 1][1], 1);
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		close(shell->pipes[i + 1][0]);
		close(shell->pipes[i + 1][1]);
		builtin = ft_check_builtins(shell, cmd);
		if (!builtin)
		{
			ft_get_cmd(shell, cmd->cmd);
			execve(shell->command_path, cmd->cmd, shell->env);
		}
		// perror("");
	}
}

void	last_c(t_cmd *cmd, t_shell *shell, int i)
{
	int	builtin;

	builtin = 0;
	close(shell->pipes[i][1]);
	dup2(shell->pipes[i][0], 0);
	close(shell->pipes[i][0]);
	close(shell->pipes[i][1]);
	builtin = ft_check_builtins(shell, cmd);
	if (!builtin)
	{
		ft_get_cmd(shell, cmd->cmd);
		execve(shell->command_path, cmd->cmd, shell->env);
	}
	// perror("");
}
