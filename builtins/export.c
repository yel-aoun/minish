/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:48:00 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/24 10:38:13 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_help_writing(char *str)
{
	int	j;
	int	k;

	j = -1;
	k = 0;
	if (ft_strcmp(str, ""))
	{
		write (1, "declare -x ", 11);
		k = ft_write(str);
		if (k == 1)
			write(1, "\"", 1);
		write (1, "\n", 1);
	}
}

int	ft_check(char *str, int k)
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
				!(str[i] == '_') && !(str[i] >= '0' && str[i] <= '9') && \
				!(str[i] == '+' && str[i + 1] == '\0' && k == 1))
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

int	ft_search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_valid_name(char	*s)
{
	int		i;
	char	**str;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == '+')
		{
			if (s[i + 1] == '=')
			{
				k = 1;
				break ;
			}
		}
		i++;
	}
	if (s && (!(s[0] >= 'a' && s[0] <= 'z') && \
		!(s[0] >= 'A' && s[0] <= 'Z') && !(s[0] == '_')))
		return (0);
	str = ft_split(s, '=');
	return (ft_check(str[0], k));
}

int	ft_put_export(t_shell *shell, char *str)
{
	int		i;

	i = 0;
	if (!str)
	{
		while (shell->export[i])
		{
			if (ft_strcmp(shell->export[i], ""))
				ft_help_writing(shell->export[i]);
			i++;
		}
	}
	else
		ft_up_help(shell, str);
	return (1);
}
