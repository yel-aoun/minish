/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:45:50 by araysse           #+#    #+#             */
/*   Updated: 2022/09/20 14:42:42 by yel-aoun         ###   ########.fr       */
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
		//printf("pizzaaaa %s\n", str);
		return (str);
	}
	else
		return (str = lexer_get_current_char_as_atring(lexer));
}

char *get_alnum(char *str, lexer_t *lexer)
{
	char *s;
	int		i;
	int		j;
	i = 0;
	j = 0;
	while(isalnum(str[i]))
		i++;
	s = malloc(sizeof(char) * i + 1);
	while (isalnum(str[j]))
	{
		s[j] = str[j];
		j++;
		lexer_advance(lexer);
	}
	s[j] = '\0';
	//printf("houuuuuch %s\n", s);
	return(s);
}

char	*find_in_env2(lexer_t *lexer, char **env)
{
	char	*str;
	
	str = NULL;
	if (lexer->c == '$')
	{
		str = ft_find_in_path(env, get_alnum(&(lexer->contents[lexer->i + 1]), lexer));
		//printf("pizzaaaa %s\n", str);
		return (str);
	}
	else if (isalnum(lexer->c))
		return (str = lexer_get_current_char_as_atring(lexer));
	else
		return ("");
}