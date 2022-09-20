/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:52:47 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/16 21:34:38 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

typedef struct s_exe
{
	char	**cmd;
}		t_exe;

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

int	co_unt(char *str, int c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == c)
			k++;
		i++;
	}
	return (k);
}

void	ex_betw(t_shell *shell, t_exe *cmds, int k)
{
	int	i;

	i = 0;
	while (i < k - 1)
	{
		pipe(shell->pipes[i + 1]);
		between_c(cmds[i + 1].cmd, shell, i);
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

void	execute_cmds(t_exe *cmds, t_shell *shell, int k)
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
		first_c(cmds[0].cmd, shell, k);
	else
	{
		if (k > 0)
		{
			ex_betw(shell, cmds, k);
			pid2 = fork();
			if (pid2 == 0)
				last_c(cmds[k].cmd, shell, k - 1);
			else
				ft_close(shell, k);
		}
		while (wait(NULL) != -1)
		{
		}
	}
}

void	exec(t_shell *shell, char *str)
{
	int		i;
	int		k;
	char	**s;
	t_exe	*cmds;

	i = 0;
	s = ft_split(str, '|');
	k = co_unt(str, '|');
	cmds = malloc((k + 1) * sizeof(t_exe));
	while (s[i])
	{
		cmds[i].cmd = ft_split(s[i], ' ');
		i++;
	}
	execute_cmds(cmds, shell, k);
}
