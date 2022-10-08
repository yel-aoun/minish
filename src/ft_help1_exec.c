/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help1_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:09:33 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/08 15:08:50 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_help_open_her_doc(t_shell *shell, t_redir *redirection, int i)
{
	pid_t	id;
	int		seg;

	seg = 0;
	pipe(shell->pip_herdoc[i]);
	id = fork();
	if (id == 0)
	{
		ft_open_heredoc(shell, redirection, i);
		exit (0);
	}
	else
		waitpid(id, &seg, 0);
	if (seg == 2)
	{
		shell->t_sig_c = 1;
		g_glob[1] = 1;
	}
	return (seg);
}

int	ft_do_somthing(t_shell *shell, int i)
{
	if (shell->new_neud == 1)
	{
		i++;
		shell->new_neud = 0;
		return (i);
	}
	else
		return (i);
}

void	ft_help_check_her_doc(t_shell *shell, t_cmd *cmd, t_redir *redirection)
{
	int	i;
	int	seg;

	i = 0;
	seg = 0;
	while (redirection)
	{
		if (ft_strcmp(redirection->type, "<<") == 0)
		{
			i = ft_do_somthing(shell, i);
			if (redirection->value == NULL)
			{
				shell->h_c = 1;
				printf("bash: syntax error near unexpected token `newline'\n");
				break ;
			}
			seg = ft_help_open_her_doc(shell, redirection, i);
			if (seg == 2)
				break ;
			cmd->infile = shell->pip_herdoc[i][0];
			cmd->outfile = shell->pip_herdoc[i][1];
			close(cmd->outfile);
		}
		redirection = redirection->next;
	}
}

void	ft_check_her_doc(t_shell *shell, t_cmd *command)
{
	t_cmd			*cmd;
	t_redir			*redirection;

	cmd = command;
	shell->new_neud = 0;
	shell->t_sig_c = 0;
	while (cmd)
	{
		redirection = cmd->redirection;
		if (redirection)
			shell->new_neud = 1;
		ft_help_check_her_doc(shell, cmd, redirection);
		if (shell->t_sig_c == 1)
			break ;
		shell->new_neud = 0;
		cmd = cmd->next;
	}
}
