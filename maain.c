/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maain.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 15:53:27 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/20 14:03:27 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;
	char	*str;

	shell = malloc(sizeof(t_shell));
	// shell->sh = malloc(sizeof(t_sh));
	shell->argc = argc;
	shell->argv = argv;
	// shell->env = env;
	ft_init_env(shell, env);
	if (shell->argc > 1)
	{
		printf("Need no arguments !!\n");
		return (0);
	}
	while (1)
	{
		// write (1, "\n", 1);
		//signal(SIGINT, hundler);
		str = readline(YELLOW "MINI_F**SHELL " WHITE);
		add_history(str);
		if (ft_strcmp(str, ""))
			ft_check_builtins(shell, str);
		// exec(shell, str);
		free (str);
	}
}
