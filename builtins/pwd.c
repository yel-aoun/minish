/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:44:19 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/07 16:12:52 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_put_pwd(t_shell *shell)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
	{
		if (shell->pwd)
			printf("ssss%s\n", shell->pwd);
		else
			printf("pwd: error: getcwd: cannot access parent directories\n");
		free(s);
		g_glob[1] = 1;
		return (1);
	}
	write (1, s, strlen(s));
	write (1, "\n", 1);
	g_glob[1] = 0;
	free(shell->pwd);
	free(s);
	return (1);
}
