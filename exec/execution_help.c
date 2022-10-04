/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 20:42:11 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/04 18:30:08 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_open_files_help(t_shell *shell, t_cmd *cmd, char *type, char *value)
{
	if (ft_strcmp(type, "<<") == 0)
	{
		shell->in = 1;
		dup2(cmd->infile, 0);
		close(cmd->outfile);
	}
	else if (ft_strcmp(type, "<") == 0)
		ft_open(1, value, shell);
	else if (ft_strcmp(type, ">") == 0)
		ft_open(2, value, shell);
	else if (ft_strcmp(type, ">>") == 0)
		ft_open(3, value, shell);
}

void	ft_open_files(t_shell *shell, t_cmd *command)
{
	int				i;
	t_cmd			*cmd;
	t_redir	*redirection;

	i = 0;
	shell->exit_creat = 0;
	shell->in = 0;
	shell->out = 0;
	cmd = command;
	redirection = cmd->redirection;
	while (redirection)
	{
		ft_open_files_help (shell, cmd, redirection->type, redirection->value);
		if (shell->exit_creat == 1)
			break ;
		else
			redirection = redirection->next;
	}
}

void	ft_close_files(t_cmd *command)
{
	t_cmd			*cmd;
	t_redir	*redirection;

	cmd = command;
	while (cmd)
	{	
		redirection = cmd->redirection;
		while (redirection)
		{
			if (ft_strcmp(redirection->type, "<<") == 0)
			{
				close(cmd->infile);
				close(cmd->outfile);
			}
			redirection = redirection->next;
		}
		cmd = cmd->next;
	}
}

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
	int		i;
	t_cmd	*count;

	i = 0;
	count = cmd;
	while (count->next)
	{
		count = count->next;
		i++;
	}
	return (i);
}
