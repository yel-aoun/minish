/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 12:07:15 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/24 09:07:10 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_write(char *str)
{
	int	l;
	int	j;
	int	k;

	j = 0;
	l = 1;
	k = 0;
	while (str[j])
	{
		write(1, &str[j], 1);
		if (str[j] == '=')
		{
			if (l == 1)
			{
				write(1, "\"", 1);
				k = 1;
				l = 0;
			}
		}
		j++;
	}
	return (k);
}

void	ft_up_help(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	if (ft_valid_name(str) == 1)
	{
		i = ft_search(str, '=');
		if (i == 1)
			shell->env = ft_add_env(shell, shell->env, str);
		shell->export = ft_add_export(shell, shell->export, str);
	}
	else
		printf("bash: export: `%s': not a valid identifier\n", str);
}
