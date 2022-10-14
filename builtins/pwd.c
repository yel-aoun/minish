/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:44:19 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/12 10:34:47 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_put_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	if (!s)
	{
		printf("pwd: error: getcwd: cannot access parent directories\n");
		free(s);
		g_glob[1] = 1;
		return (1);
	}
	write (1, s, strlen(s));
	write (1, "\n", 1);
	g_glob[1] = 0;
	free(s);
	return (1);
}
