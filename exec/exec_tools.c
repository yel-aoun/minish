/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:51:37 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/14 10:04:46 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_err_cmd(char *str, int k)
{
	write(2, str, ft_strlen(str));
	write (2, ": ", 2);
	if (k == 1)
	{
		write (2, "command not found\n", \
			ft_strlen("command not found\n"));
		exit(0);
	}
	else if (k == 2)
	{
		write (2, "No such file or directory\n", \
			ft_strlen("No such file or directory\n"));
		exit (127);
	}
}

void	ft_error(char *str)
{
	perror (str);
	exit (0);
}
