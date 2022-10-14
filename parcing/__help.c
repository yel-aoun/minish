/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __help.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:52:42 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/14 11:54:00 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*struct_cmd(t_lexer *lexer, t_token *token, char *str, char **env)
{
	char	*s;

	(void)lexer;
	(void)env;
	if (token->value)
	{
		s = ft_getchar(127);
		str = ft_tstrjoin(str, token->value);
		str = ft_tstrjoin(str, s);
	}
	return (str);
}

char	**return_null(void)
{
	char	**str;

	str = malloc(sizeof(char *));
	str[0] = NULL;
	return (str);
}
