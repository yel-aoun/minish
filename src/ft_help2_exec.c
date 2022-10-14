/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help2_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:41:59 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/12 12:34:41 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_help_open_her_doc_2(t_redir *redirection, int j, char *limiter)
{
	if (!limiter)
	{
		free(limiter);
		g_glob[1] = 0;
		exit(0);
	}
	j = ft_strncmp(limiter, redirection->value, \
		ft_is_longer(limiter, redirection->value));
	return (j);
}

void	ft_open_heredoc(t_shell *shell, t_redir *redirection, int i)
{
	int		j;
	char	*limiter;

	close(shell->pip_herdoc[i][0]);
	while (1)
	{
		j = 1;
		limiter = readline("> ");
		j = ft_help_open_her_doc_2(redirection, j, limiter);
		if (j)
		{
			write(shell->pip_herdoc[i][1], limiter, ft_strlen(limiter));
			write(shell->pip_herdoc[i][1], "\n", 1);
			free(limiter);
		}
		else
		{
			free(limiter);
			break ;
		}
	}
}
