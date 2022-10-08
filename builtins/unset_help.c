/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:41:31 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/05 12:04:45 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_do_unset(t_shell *shell, t_cmd *cmd, int i)
{
	shell->env = update_env(shell, cmd->cmd[i]);
	shell->export = update_export(shell, cmd->cmd[i]);
	g_glob[1] = 0;
}

int	ft_valid_unset(char *str)
{
	int	i;

	i = 0;
	if (str && ((str[0] >= 'a' && str[0] <= 'z') || \
		(str[0] >= 'A' && str[0] <= 'Z') || str[0] == '_'))
	{
		while (str[i])
		{
			if (!(str[i] >= 'a' && str[i] <= 'z') && \
				!(str[i] >= 'A' && str[i] <= 'Z') && \
				!(str[i] == '_') && !(str[i] >= '0' && str[i] <= '9'))
			{
				return (0);
			}
			i++;
		}
		return (1);
	}
	else
		return (0);
}
