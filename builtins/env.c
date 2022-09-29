/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:37:30 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/29 18:57:19 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_env_err(char *str)
{
	write (2, "env: ", 5);
	write (2, str, ft_strlen(str));
	write (2, ": No such file or directory", \
		ft_strlen(": No such file or directory"));
	g_glob[1] = 127;
}

int	ft_put_env(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->cmd[1])
	{
		while (shell->env[i])
		{
			if (ft_strcmp(shell->env[i], ""))
			{
				printf("%s\n", shell->env[i]);
			}
			i++;
		}
		g_glob[1] = 0;
	}
	else
		ft_env_err(cmd->cmd[1]);
	return (1);
}
