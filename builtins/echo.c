/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:22:21 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/30 15:44:54 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_str_skip(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0)
		{
			if (str[0] == '-')
				i++;
			else
				return (0);
		}
		else
		{
			if (str[i] == 'n')
				i++;
			else
				return (0);
		}
	}
	return (1);
}

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_put_words(t_cmd *cmd, int i)
{
	while (cmd->cmd[i])
	{
		ft_putstr(cmd->cmd[i]);
		if (cmd->cmd[i + 1])
			ft_putchar(' ');
		i++;
	}
}

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	endl;

	i = 1;
	endl = 1;
	if (!cmd->cmd[i])
	{
		ft_putchar('\n');
		g_glob[1] = 0;
		return (1);
	}
	while (cmd->cmd[i] && ft_str_skip(cmd->cmd[i]))
	{
		endl = 0;
		i++;
	}
	ft_put_words(cmd, i);
	if (endl)
		ft_putchar('\n');
	g_glob[1] = 0;
	return (1);
}
