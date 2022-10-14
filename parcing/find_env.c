/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:45:50 by araysse           #+#    #+#             */
/*   Updated: 2022/10/13 23:26:59 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*find_in_env(t_lexer *lxr, char **env)
{
	char	*str;

	str = NULL;
	if (lxr->c == '$')
	{
		if (lxr->contents[lxr->i + 1] == '?')
		{
			lexer_advance(lxr);
			return (ft_itoa(g_glob[1]));
		}
		if (lxr->contents[lxr->i + 1] == '\0')
			return (lxr_as_str(lxr));
		str = f_in_path(env, get_alnum(&(lxr->contents[lxr->i + 1]), lxr));
		return (str);
	}
	else
		return (lxr_as_str(lxr));
}

char	*get_alnum(char *str, t_lexer *lexer)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	s = malloc(sizeof(char) * i + 1);
	while (ft_isalnum(str[j]) || str[j] == '_')
	{
		s[j] = str[j];
		j++;
		lexer_advance(lexer);
	}
	s[j] = '\0';
	return (s);
}

char	*find_in_env2(t_lexer *lxr, char **env)
{
	char	*str;

	str = NULL;
	if (lxr->c == '$' && lxr->c)
	{
		if (lxr->contents[lxr->i + 1] == '?')
		{
			lexer_advance(lxr);
			return (ft_itoa(g_glob[1]));
		}
		if (lxr->contents[lxr->i + 1] == '\0')
			return (lxr_as_str(lxr));
		str = f_in_path(env, get_alnum(&(lxr->contents[lxr->i + 1]), lxr));
		return (str);
	}
	else if (lxr->c != ' ')
		return (lxr_as_str(lxr));
	else
		return ("");
}
