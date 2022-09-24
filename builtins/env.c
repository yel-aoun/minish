/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:37:30 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/24 14:46:14 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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
	}
	else
		ft_err_cmd(cmd->cmd[0], 3);
	return (1);
}
