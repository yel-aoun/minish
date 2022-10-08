/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:56:56 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/08 16:52:51 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_check_valide_files(t_shell *shell, t_cmd *command)
{
	int				i;
	t_cmd			*cmd;
	t_redir			*redirection;

	i = 0;
	shell->err = 0;
	cmd = command;
	while (cmd)
	{
		redirection = cmd->redirection;
		while (redirection)
		{
			if ((ft_strcmp(redirection->type, "<") == 0 && \
				redirection->value == NULL))
				shell->err = 1;
			else if ((ft_strcmp(redirection->type, ">") == 0 && \
				redirection->value == NULL))
				shell->err = 1;
			else if ((ft_strcmp(redirection->type, ">>") == 0 && \
				redirection->value == NULL))
				shell->err = 1;
			redirection = redirection->next;
		}
		cmd = cmd->next;
	}
}

int	ft_count_herdoc_pipes(t_cmd *command)
{
	t_cmd	*cmd;
	t_redir	*redirection;
	int		i;

	cmd = command;
	i = 0;
	while (cmd)
	{
		redirection = cmd->redirection;
		while (redirection)
		{
			if (ft_strcmp (redirection->type, "<<") == 0)
			{
				i++;
				break ;
			}
			redirection = redirection->next;
		}
		cmd = cmd->next;
	}
	return (i);
}

void	ft_create_pipes_heredoc(t_shell *shell, int k)
{
	int	i;

	i = 0;
	shell->pip_herdoc = malloc(sizeof(int *) * k);
	if (!shell->pip_herdoc)
		return ;
	while (i < k)
	{
		shell->pip_herdoc[i] = malloc(sizeof(int) * 2);
		i++;
	}
}

void	ft_free_heredoc(t_shell *shell, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(shell->pip_herdoc[i]);
		i++;
	}
	free(shell->pip_herdoc);
}

void	ft_get_exec(t_shell *shell, t_cmd *command)
{
	int		k;
	t_cmd	*cmd;

	k = 0;
	cmd = command;
	shell->h_c = 0;
	ft_check_valide_files(shell, cmd);
	if (shell->err == 0)
	{
		k = ft_count_herdoc_pipes(cmd);
		if (k)
			ft_create_pipes_heredoc(shell, k);
		ft_check_her_doc(shell, cmd);
		if (shell->h_c == 0 && shell->t_sig_c == 0)
			exec(shell, cmd);
		if (k)
			ft_free_heredoc(shell, k);
	}
	else
		printf("bash: syntax error near unexpected token `newline '\n");
}
