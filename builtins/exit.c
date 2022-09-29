/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:52:44 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/29 17:18:25 by yel-aoun         ###   ########.fr       */
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

void	ft_exit(t_cmd *cmd, int p)
{
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		if (is_digit(cmd->cmd[1]))
		{
			if (p == 0)
				printf("exit\n");
			write (2, "bash: exit: too many arguments\n", 31);
			g_glob[1] = 1;
		}
		else
		{
			if (p == 0)
				write (2, "exit\n", 5);
			write(2,"bash: exit: ", 12);
			write (2, cmd->cmd[1], ft_strlen(cmd->cmd[1]));
			write (2, ": numeric argument required\n", 28);
			exit(255);
			g_glob[1] = 255;
		}
	}
    else if(!is_digit(cmd->cmd[1]))
    {
		if (p == 0)
			printf("exit\n");
		write(2,"bash: exit: ", 12);
		write (2, cmd->cmd[1], ft_strlen(cmd->cmd[1]));
		write (2, ": numeric argument required\n", 28);
		exit (255);
		g_glob[1] = (255);
	}
	else if(is_digit(cmd->cmd[1]) == 1)
	{
		if (p == 0)
			write (2, "exit\n", 5);
		exit (ft_atoi(cmd->cmd[1]) % 256);
		g_glob[1] = (ft_atoi(cmd->cmd[1]) % 256);
	}
	else
	{
		if (p == 0)
			printf("exit\n");
		exit(0);
		g_glob[1] = 0;
	}
	//g_glob[1] = 0;
}