/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 18:09:14 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/30 18:26:51 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_first_cmd_help(t_shell *shell, t_cmd *cmd)
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

void	ft_help_between_c(t_shell *shell, t_cmd *cmd, int i)
{
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
}
