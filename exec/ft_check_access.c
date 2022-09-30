/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 21:25:07 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/30 21:25:31 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_help_print_err_fille(char *err)
{
	write (2, "bash: ", 6);
	write (2, err, ft_strlen(err));
	write (2, ":", 1);
	perror("");
}

void	ft_help_check_access(char *arg, t_shell *shell)
{
	if (access(arg, F_OK) == -1)
	{
		ft_help_print_err_fille(arg);
		shell->exit_creat = 1;
		g_glob[1] = 1;
	}
}

void	ft_check_access(char *arg, int n, t_shell *shell)
{
	if (n == 0)
	{
		if (access(arg, R_OK) == -1)
		{
			ft_help_print_err_fille(arg);
			shell->exit_creat = 1;
			g_glob[1] = 1;
		}
	}
	if (n == 1)
	{
		if (access(arg, W_OK) == -1)
		{
			ft_help_print_err_fille(arg);
			shell->exit_creat = 1;
			g_glob[1] = 1;
		}
	}
	if (n == 2)
		ft_help_check_access(arg, shell);
}
