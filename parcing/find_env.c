/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:45:50 by araysse           #+#    #+#             */
/*   Updated: 2022/10/01 15:18:28 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*find_in_env(lexer_t *lexer, char **env)
{
	char	*str;
	
	str = NULL;
	if (lexer->c == '$')
	{
		str = ft_find_in_path(env, get_alnum(&(lexer->contents[lexer->i + 1]), lexer));
		return (str);
	}
	if (lexer->c == '?')
		return (ft_itoa(g_glob[1]));
	else
		return (lexer_get_current_char_as_atring(lexer));
}

char *get_alnum(char *str, lexer_t *lexer)
{
	char *s;
	int		i;
	int		j;
	i = 0;
	j = 0;
	while(ft_isalnum(str[i]) || str[i] == '_')
		i++;
	s = malloc(sizeof(char) * i + 1);
	while (ft_isalnum(str[j]) || str[j]== '_')
	{
		s[j] = str[j];
		j++;
		lexer_advance(lexer);
	}
	s[j] = '\0';
	return(s);
}

char	*find_in_env2(lexer_t *lexer, char **env)
{
	char	*str;
	
	str = NULL;
	if (lexer->c == '$')
	{
		str = ft_find_in_path(env, get_alnum(&(lexer->contents[lexer->i + 1]), lexer));
		return (str);
	}
	if (lexer->c == '?')
		return (ft_itoa(g_glob[1]));
	else if (lexer->c != ' ')
		return (str = lexer_get_current_char_as_atring(lexer));
	else
		return ("");
} 