/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:00:57 by araysse           #+#    #+#             */
/*   Updated: 2022/10/04 19:07:16 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

lexer_t	*init_lexer(char *contents)
{
	lexer_t	*lexer;

	lexer = calloc(1, sizeof (struct lexer_struct));
	lexer->contents = malloc(sizeof(char) * ft_strlen(contents) + 1);
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void	lexer_advance(lexer_t *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_tstrlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(lexer_t *lexer)
{
	while (lexer->c == ' ' || lexer->c == 10)
		lexer_advance(lexer);
}

char	*lexer_collect_string(lexer_t *lexer, char **env)
{
	char	*v;
	char	*s;

	v = calloc(1, sizeof(char));
	lexer_advance(lexer);
	v[0] = '\0';
	if (lexer->c)
	{
		while (lexer->c != '"')
		{
			if (lexer->contents[lexer->i + 1] == '\0' || lexer->c == '\0')
				return (ft_eror(1));
			s = find_in_env(lexer, env);
			v = realloc(v, (ft_tstrlen(v) + ft_tstrlen(s) + 1) * sizeof(char));
			ft_strcat(v, s);
			lexer_advance(lexer);
		}
		lexer_advance(lexer);
	}
	else
		return (ft_eror(1));
	return (v);
}
