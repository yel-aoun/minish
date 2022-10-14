/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_main2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:57:50 by araysse           #+#    #+#             */
/*   Updated: 2022/10/13 11:30:26 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	col_redir(t_redir *redir, t_lexer *lexer, t_token *token, char **env)
{
	t_token	*tok1;
	t_lexer	*lexer1;
	int		i;

	i = 0;
	tok1 = NULL;
	lexer1 = init_lexer(lexer->contents);
	while (lexer1->i < lexer->i)
		increment(&tok1, lexer1, env);
	tok1 = lexer_next(lexer1, env, 2);
	free(lexer1);
	redir->type = token->value;
	if (tok1 == NULL)
		redir->value = NULL;
	else if (tok1->e_type != token_word || !(tok1->value[0]))
		free_tok1(redir, tok1);
	else if (tok1->e_type == token_word)
	{
		token = lexer_next(lexer, env, 2);
		tok1_word(redir, tok1, token);
	}
	if (tok1)
		free(tok1);
}

void	free_tok1(t_redir *redir, t_token *tok1)
{
	free(tok1->value);
	redir->value = NULL;
}

char	*ft_getchar(char c)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	is_redirection(t_token *token)
{
	if (token->e_type < 4 && token->e_type >= 0)
		return (1);
	return (0);
}

t_redir	*struct_redir(t_token *token, t_lexer *lexer, char **env)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->next = NULL;
	if (token->e_type == token_herdoc)
		col_redir(redir, lexer, token, env);
	else if (token->e_type == token_apend)
		col_redir(redir, lexer, token, env);
	else if (token->e_type == token_infile)
		col_redir(redir, lexer, token, env);
	else if (token->e_type == token_outfile)
		col_redir(redir, lexer, token, env);
	return (redir);
}
