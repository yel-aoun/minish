/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:56:56 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/01 15:55:41 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_check_valide_files(t_shell *shell, t_cmd *command)
{
	int				i;
	t_cmd			*cmd;
	t_redirection	*redirection;

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
	t_cmd			*cmd;
	t_redirection	*redirection;
	int				i;
	int				j;

	cmd = command;
	i = 0;
	j = 0;
	while (cmd)
	{
		j = 0;
		redirection = cmd->redirection;
		while (redirection)
		{
			if (j == 0)
			{
				if (ft_strcmp (redirection->type, "<<") == 0)
				{
					i++;
					j = 1;
				}
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

void	ft_open_heredoc(t_shell *shell, t_redirection *redirection, int i)
{
	int		j;
	char	*limiter;

	j = 0;
	close(shell->pip_herdoc[i][0]);
	while (1)
	{
		j = 1;
		signal(SIGINT, SIG_DFL);
		limiter = readline("> ");
		if (!limiter)
		{
			free(limiter);
			g_glob[1] = 0;
			exit(0);
		}
		j = ft_strncmp(limiter, redirection->value, \
			ft_is_longer(limiter, redirection->value));
		if (j)
		{
			write(shell->pip_herdoc[i][1], limiter, ft_strlen(limiter));
			write(shell->pip_herdoc[i][1], "\n", 1);
		}
		else
		{
			free(limiter);
			break ;
		}
	}
}

void	ft_check_her_doc(t_shell *shell, t_cmd *command)
{
	t_cmd			*cmd;
	t_redirection	*redirection;
	pid_t			id;
	int				i;
	int				seg;
	int				new_neud;

	cmd = command;
	i = -1;
	new_neud = 0;
	seg = 0;
	shell->t_sig_c = 0;
	while (cmd)
	{
		redirection = cmd->redirection;
		if (redirection)
			new_neud = 1;
		while (redirection)
		{
			if (ft_strcmp(redirection->type, "<<") == 0)
			{
				if (new_neud == 1)
				{
					i++;
					new_neud = 0;
				}
				if (redirection->value == NULL)
				{
					shell->h_c = 1;
					printf("bash: syntax error near unexpected token `newline'\n");
					break ;
				}
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
					//ft_close_insegnals(shell, i);
					break ;
				}
				cmd->infile = shell->pip_herdoc[i][0];
				cmd->outfile = shell->pip_herdoc[i][1];
				close(cmd->outfile);
			}
			redirection = redirection->next;
		}
		if (shell->t_sig_c == 1)
			break ;
		new_neud = 0;
		cmd = cmd->next;
	}
}

void	ft_get_exec(t_shell *shell, t_cmd *cmd)
{
	int	k;

	k = 0;
	shell->h_c = 0;
	ft_check_valide_files(shell, cmd);
	if (shell->err == 0)
	{
		k = ft_count_herdoc_pipes(cmd);
		ft_create_pipes_heredoc(shell, k);
		ft_check_her_doc(shell, cmd);
		if (shell->h_c == 0 && shell->t_sig_c == 0)
			exec(shell, cmd);
	}
	else
		printf("bash: syntax error near unexpected token\n");
}
