/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_main3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:58:01 by araysse           #+#    #+#             */
/*   Updated: 2022/10/08 16:40:06 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"


void	ft_sig_child(int sig)
{
	(void) sig;
	// if (sig == SIGINT)
	// rl_replace_line("", 0);
}
void	ft_sig_int(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
	}
}

void	ft_exit_sig(char *str)
{
	printf("%s\n", str);
	exit(0);
}
