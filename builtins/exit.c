/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:52:44 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/24 10:01:53 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (2);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit(t_shell *shell, t_cmd *cmd)
{
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		if (is_digit(cmd->cmd[1]))
		{
			printf("exit\n");
			printf("bash: exit: too many arguments\n");
			shell->exit_status = 1;
		}
		else
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n", cmd->cmd[1]);
			exit(255);
			shell->exit_status = 255;
		}
	}
    else if(!is_digit(cmd->cmd[1]))
    {
		printf("exit\n");
		printf("bash: exit: %s: numeric argument required\n", cmd->cmd[1]);
		exit (255);
		shell->exit_status = (255);
	}
	else if(is_digit(cmd->cmd[1]) == 1)
	{
		printf("exit\n");
		exit (ft_atoi(cmd->cmd[1]) % 256);
		shell->exit_status = (ft_atoi(cmd->cmd[1]) % 256);
	}
	else
	{
		printf("exit\n");
		exit(0);
		shell->exit_status = 0;
	}
	//shell->exit_status = 0;
}