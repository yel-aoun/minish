/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:00:57 by araysse           #+#    #+#             */
/*   Updated: 2022/10/14 11:45:04 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof (struct lexer_struct));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_tstrlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == 10)
		lexer_advance(lexer);
}

char	*lexer_collect_string(t_lexer *lexer, char **env, int k)
{
	char	*v;
	char	*s;

	v = NULL;
	lexer_advance(lexer);
	if (lexer->c == '"')
		return (ft_strdup(""));
	if (lexer->c)
	{
		while (lexer->c != '"')
		{
			if (lexer->contents[lexer->i + 1] == '\0' || lexer->c == '\0')
				return (ft_eror(v, 1, k));
			s = find_in_env(lexer, env);
			v = ft_tstrjoin(v, s);
			lexer_advance(lexer);
		}
	}
	else
		return (ft_eror(v, 1, k));
	return (v);
}
