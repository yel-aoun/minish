/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:22:21 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/14 17:42:18 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_strequ(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && !s2[i])
		return (1);
	return (0);
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

void	ft_echo(t_shell *shell)
{
	int	i;
	int	endl;

	i = 1;
	endl = 1;
	if (!shell->cmd_args[i])
	{
		ft_putchar('\n');
		return ;
	}
	while (shell->cmd_args[i] && ft_strequ(shell->cmd_args[i], "-n"))
	{
		endl = 0;
		i++;
	}
	while (shell->cmd_args[i])
	{
		ft_putstr(shell->cmd_args[i]);
		if (shell->cmd_args[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (endl)
		ft_putchar('\n');
	//shell->exit = 0;
}
