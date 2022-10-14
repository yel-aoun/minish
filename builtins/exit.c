/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 10:52:44 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/12 10:33:33 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_put_error(char *str, unsigned long long sum, int j, \
		unsigned long long numb)
{
	if (sum > numb && j == 1)
	{
		write (2, "bash: exit: ", 12);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 28);
		g_glob[1] = 255;
		exit(255);
	}
	else if (sum > (numb + 1) && j == -1)
	{
		write (2, "bash: exit: ", 12);
		write(2, str, ft_strlen(str));
		write(2, ": numeric argument required\n", 28);
		g_glob[1] = (255);
		exit(255);
	}
}

int	ft_toi(const char *s)
{
	long long			i;
	int					sign;
	unsigned long long	sum;

	i = 0;
	sign = 1;
	sum = 0;
	while (s[i] == ' ' || s[i] == '\t'
		|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r' || s[i] == '\n')
		i++;
	if (s[i] == '+' && s[i + 1] == '-')
		return (0);
	if (s[i] == '+')
		i++;
	if (s[i] == '-')
	{
		sign = sign * (-1);
		i++;
	}
	while (s[i] != '\0' && s[i] >= 48 && s[i] <= 57)
	{
		sum = sum * 10 + (s[i++] - '0');
		ft_put_error((char *)s, sum, sign, 9223372036854775807);
	}
	return (sum * sign);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (2);
	while (str[i])
	{
		if (str[0] == '-' || str[0] == '+' || (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_exit_help(t_cmd *cmd)
{
	if (!is_digit(cmd->cmd[1]))
	{
		write (2, "bash: exit: ", 12);
		write (2, cmd->cmd[1], ft_strlen(cmd->cmd[1]));
		write (2, ": numeric argument required\n", 28);
		g_glob[1] = 255;
		exit (255);
	}
	else if (is_digit(cmd->cmd[1]) == 1)
	{
		ft_toi(cmd->cmd[1]);
		g_glob[1] = (ft_atoi(cmd->cmd[1]) % 256);
		exit (ft_atoi(cmd->cmd[1]) % 256);
	}
	else
	{
		g_glob[1] = 0;
		exit(0);
	}
}

void	ft_exit(t_cmd *cmd, int p)
{
	if (p == 0)
		write (2, "exit\n", 5);
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		if (is_digit(cmd->cmd[1]))
		{
			write (2, "bash: exit: too many arguments\n", 31);
			g_glob[1] = 1;
		}
		else
		{
			write (2, "bash: exit: ", 12);
			write (2, cmd->cmd[1], ft_strlen(cmd->cmd[1]));
			write (2, ": numeric argument required\n", 28);
			g_glob[1] = 255;
			exit(255);
		}
	}
	else
		ft_exit_help(cmd);
}
