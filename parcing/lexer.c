/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:06:52 by araysse           #+#    #+#             */
/*   Updated: 2022/09/29 14:25:24 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

lexer_t		*init_lexer(char *contents)
{
	lexer_t *lexer = calloc(1, sizeof (struct lexer_struct));
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
	while (lexer->c == ' ' || lexer->c ==  10)
	{
		lexer_advance(lexer);
	}
}
token_t	*lexer_get_next_token(lexer_t *lexer, char **env)
{
	while (lexer->c != '\0')
	{
		if (lexer->c == ' ' || lexer->c ==  10)
			lexer_skip_whitespace(lexer);
		if (lexer->c == '<')
			return (lexer_infile(lexer));
		if (lexer->c == '>')
			return (lexer_outfile(lexer));
		if (lexer->c == '|')
			return(lexer_advance_with_token(lexer, init_token(token_pipe, lexer_get_current_char_as_atring(lexer))));
		return lexer_collect_id(lexer, env);
	}
	return (NULL);
}

char	*lexer_collect_string(lexer_t *lexer, char **env)
{
	lexer_advance(lexer);
	char *value = calloc(1, sizeof(char));
	char	*s;
	value[0] = '\0';
		
	while (lexer->c != '"')
	{
		if (lexer->contents[lexer->i] == '\0')
			return (ft_eror(1));
		s = find_in_env(lexer, env);
		value = realloc(value, (ft_tstrlen(value) + ft_tstrlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		
		lexer_advance(lexer);
	}
	//lexer_advance(lexer);
	return (value);
}

token_t	*lexer_advance_with_token(lexer_t *lexer, token_t *token)
{
	lexer_advance(lexer);
	return token;
}

token_t *lexer_collect_id(lexer_t *lexer, char **env)
{
	char *value = calloc(1, sizeof(char));
	char *str;
	
	value[0] = '\0';
	str = NULL;
	while (lexer->c != ' ' && lexer->c && lexer->c != '"' && lexer->c != '\'' && lexer->c != '<' && lexer->c != '>' && lexer->c != '|')
	{
		char	*s = find_in_env2(lexer, env);
			
		value = realloc(value, (ft_tstrlen(value) + ft_tstrlen(s) + 1) * sizeof(char));
		strcat(value, s);
		lexer_advance(lexer);
	}
	if (lexer->c == '"')
		str = lexer_collect_string(lexer, env);
	if (lexer->c == '\'')
		str = lexer_collect_single_quot(lexer);
	value = realloc(value, (ft_tstrlen(value) + ft_tstrlen(str) + 1) * sizeof(char));
	ft_strcat(value, str);
	if (value && !value[0])
        return (init_token(token_word, NULL));
	return (init_token(token_word, value));
}

char	*lexer_get_current_char_as_atring(lexer_t	*lexer)
{
	char *str = calloc(2, sizeof(char));
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
		return (init_token(token_herdoc, value));
	}
	return lexer_advance_with_token(lexer, init_token(token_infile, lexer_get_current_char_as_atring(lexer)));
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
		return (init_token (token_apend, value));
	}
	return lexer_advance_with_token(lexer, init_token(token_outfile, lexer_get_current_char_as_atring(lexer)));
}

char	*lexer_collect_single_quot(lexer_t *lexer)
{
	lexer_advance(lexer);
	char *value = calloc(1, sizeof(char));
	value[0] = '\0';
	while (lexer->c != '\'')
	{
		if (lexer->contents[lexer->i + 1] == '\0')
			return (ft_eror(1));
		char	*s = lexer_get_current_char_as_atring(lexer);
		value = realloc(value, (ft_tstrlen(value) + ft_tstrlen(s) + 1) * sizeof(char));
		strcat(value, s);
		
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	
	return (value);
}

char	*ft_eror(int i)
{
	if (i == 1)
	{
		printf("unclosed quots\n");
		return (NULL);
	}
	if (i == 2)
	{
		printf("unispected token\n");
		return (NULL);
	}
	return (0);
}