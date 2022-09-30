/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:36:15 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/30 13:48:23 by yel-aoun         ###   ########.fr       */
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
