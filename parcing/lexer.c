/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:06:52 by araysse           #+#    #+#             */
/*   Updated: 2022/10/14 11:46:54 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*lexer_collect_single_quot(t_lexer *lexer, int k)
{
	char	*v;
	char	*s;

	lexer_advance(lexer);
	if (lexer->c == '\'')
		return (ft_strdup(""));
	v = NULL;
	if (lexer->c)
	{
		while (lexer->c != '\'')
		{
			if (lexer->contents[lexer->i + 1] == '\0')
				return (ft_eror(v, 1, k));
			s = lxr_as_str(lexer);
			v = ft_tstrjoin(v, s);
			lexer_advance(lexer);
		}
	}
	else
		return (ft_eror(v, 1, k));
	return (v);
}

char	*ft_eror(char *s, int i, int k)
{
	free(s);
	if (i == 1)
	{
		if (k == 1)
		{
			printf("unclosed quots\n");
			g_glob[0] = 1;
		}
		return (NULL);
	}
	return (0);
}

int	valid_char(t_lexer *lexer)
{
	if (lexer->c != ' ' && lexer->c && lexer->c != '<'
		&& lexer->c != '>' && lexer->c != '|')
		return (1);
	return (0);
}

t_token	*lexer_next(t_lexer *lexer, char **env, int k)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ' || lexer->c == 10)
			lexer_skip_whitespace(lexer);
		if (lexer->c == '<')
			return (lexer_infile(lexer));
		if (lexer->c == '>')
			return (lexer_outfile(lexer));
		if (lexer->c == '|')
			return (lxr_ad_tok(lexer, init_tok(token_pipe, lxr_as_str(lexer))));
		return (lexer_collect_id(lexer, env, k));
	}
	return (NULL);
}
