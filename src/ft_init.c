/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:36:15 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/28 18:02:40 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_init_env(t_shell *shell, char **new)
{
	// shell->env = malloc(sizeof(char **) * ft_count(new) + 1);
	// shell->export = malloc(sizeof(char **) * ft_count(new) + 1);
	// if (!shell->env || !shell->export)
	// 	return ;
	shell->in = 0;
	shell->out = 0;
	ft_export(shell, new);
	ft_env(shell, new);
}
