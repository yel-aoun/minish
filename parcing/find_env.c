/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:45:50 by araysse           #+#    #+#             */
/*   Updated: 2022/10/05 12:31:26 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*find_in_env(lexer_t *lxr, char **env)
{
	char	*str;

	str = NULL;
	if (lxr->c == '$')
	{
		str = f_in_path(env, get_alnum(&(lxr->contents[lxr->i + 1]), lxr));
		return (str);
	}
	if (lxr->c == '?')
		return (ft_itoa(g_glob[1]));
	else
		return (lxr_as_str(lxr));
}

char	*get_alnum(char *str, lexer_t *lexer)
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
	free (str);
	s[j] = '\0';
	return (s);
}

char	*find_in_env2(lexer_t *lxr, char **env)
{
	char	*str;

	str = NULL;
	if (lxr->c == '$')
	{
		str = f_in_path(env, get_alnum(&(lxr->contents[lxr->i + 1]), lxr));
		return (str);
	}
	if (lxr->c == '?')
		return (ft_itoa(g_glob[1]));
	else if (lxr->c != ' ')
		return (lxr_as_str(lxr));
	else
		return ("");
}
