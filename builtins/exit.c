/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:52:44 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/20 10:07:13 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit(t_shell *shell)
{
	if (shell->cmd_args[1] && shell->cmd_args[2])
	{
		if (is_digit(shell->cmd_args[1]))
		{
			printf("exit\n");
			printf("bash: exit: too many arguments\n");
			//exit status == 1
		}
		else
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n", shell->cmd_args[1]);
			exit(255);
			
		}
	}
    else if(!is_digit(shell->cmd_args[1]))
    {
		if(!is_digit(shell->cmd_args[1]))
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required\n", shell->cmd_args[1]);
			exit (255);
		}
	}
	else
	{
		printf("heer\n");
		printf("exit\n");
		exit(0);
	}
}