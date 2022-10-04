/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 15:08:22 by araysse           #+#    #+#             */
/*   Updated: 2022/10/04 15:09:50 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

token_t	*lxr_ad_tok(lexer_t *lexer, token_t *token)
{
	lexer_advance(lexer);
	return (token);
}

token_t	*lexer_collect_id(lexer_t *lexer, char **env)
{
	char	*v;
	char	*str;
	char	*s;

	v = calloc(1, sizeof(char));
	v[0] = '\0';
	str = NULL;
	while (valid_char(lexer))
	{
		s = find_in_env2(lexer, env);
		v = realloc(v, (ft_tstrlen(v) + ft_tstrlen(s) + 1) * sizeof(char));
		strcat(v, s);
		lexer_advance(lexer);
	}
	if (lexer->c == '"')
		str = lexer_collect_string(lexer, env);
	if (lexer->c == '\'')
		str = lexer_collect_single_quot(lexer);
	v = realloc(v, (ft_tstrlen(v) + ft_tstrlen(str) + 1) * sizeof(char));
	ft_strcat(v, str);
	if (v && !v[0])
		return (init_tok(token_word, NULL));
	return (init_tok(token_word, v));
}

char	*lxr_as_str(lexer_t	*lexer)
{
	char	*str;

	str = calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

token_t	*lexer_infile(lexer_t *lexer)
{
	char	*value;

	if (lexer->contents[lexer->i + 1] == '<')
	{
		value = malloc(3 * sizeof(char));
		value[0] = lexer->c;
		value[1] = lexer->contents[lexer->i + 1];
		value[2] = '\0';
		lexer_advance(lexer);
		lexer_advance(lexer);
		return (init_tok(token_herdoc, value));
	}
	return (lxr_ad_tok(lexer, init_tok(token_infile, lxr_as_str(lexer))));
}

token_t	*lexer_outfile(lexer_t *lexer)
{
	char	*value;

	if (lexer->contents[lexer->i + 1] == '>')
	{
		value = malloc(3 * sizeof(char));
		value[0] = lexer->c;
		value[1] = lexer->contents[lexer->i + 1];
		value[2] = '\0';
		lexer_advance(lexer);
		lexer_advance(lexer);
		return (init_tok (token_apend, value));
	}
	return (lxr_ad_tok(lexer, init_tok(token_outfile, lxr_as_str(lexer))));
}
