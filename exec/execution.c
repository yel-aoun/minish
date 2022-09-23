/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:52:47 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/23 11:48:20 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// typedef struct s_exe
// {
// 	char	**cmd;
// }		t_exe;

void	ft_close(t_shell *shell, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

int	co_unt(t_cmd *cmd)
{
	int	i;
	t_cmd *count;
	// int	k;

	i = 0;
	count = cmd;
	// k = 0;
	// while (str[i])
	// {
	// 	if (str[i] == c)
	// 		k++;
	// 	i++;
	// }
	// return (k);
	while (count)
	{
		count = count->next;
		i++;
	}
	return (i);
}

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
		between_c(cmd->cmd, shell, i);
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
		cmd = cmd->next;
	}
}

void	execute_cmds(t_cmd *cmd, t_shell *shell, int k)
{
	int		i;
	pid_t	pid;
	pid_t	pid2;

	i = 0;
	ft_creat_pipes(shell, k);
	pid = fork();
	if (pid == -1)
	{
		printf("bash: fork: Resource temporarily unavailable\n");
		return ;
	}
	if (pid == 0)
		first_c(cmd->cmd, shell, k);
	else
	{
		if (k > 0)
		{
			ex_betw(shell, cmd, k);
			pid2 = fork();
			if (pid2 == 0)
			{
				while (cmd->next)
				{
					cmd = cmd->next;
				}
				last_c(cmd->cmd, shell, k - 1);
			}
			else
				ft_close(shell, k);
		}
		while (wait(NULL) != -1)
		{
		}
	}
}

void	exec(t_shell *shell, t_cmd *cmd)
{
	int		k;

	k = co_unt(cmd);
	execute_cmds(cmd, shell, k);
}
