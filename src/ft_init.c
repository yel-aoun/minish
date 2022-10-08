/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:36:15 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/08 17:45:56 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_init_env(t_shell *shell, char **new)
{
	shell->in = 0;
	shell->out = 0;
	ft_export(shell, new);
	ft_env(shell, new);
}

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_pipes(int **arr, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
