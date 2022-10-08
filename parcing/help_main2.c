// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_main2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:57:50 by araysse           #+#    #+#             */
/*   Updated: 2022/10/05 21:18:47 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	col_redir(t_redir *redir, lexer_t *lexer, token_t *token, char **env)
{
	token_t	*tok1;
	lexer_t	*lexer1;
	int		i;

	i = 0;
	lexer1 = init_lexer(lexer->contents);
	while (lexer1->i < lexer->i)
	{
		tok1 = lexer_next(lexer1, env);
		free(tok1->value);
		free (tok1);
	}
	tok1 = lexer_next(lexer1, env);
	free(lexer1);
	redir->type = token->value;
	if (tok1 == NULL)
		redir->value = NULL;
	else if (tok1->type != token_word)
	{
		free(tok1->value);
		redir->value = NULL;
	}
	else if (tok1->type == token_word)
	{
		redir->value = tok1->value;
		token = lexer_next(lexer, env);
		if (token)
		{
			free (token ->value);
			free(token);
		}
	}
	if (tok1)
		free(tok1);
}

char	*struct_cmd(lexer_t *lexer, token_t *token, char *str, char **env)
{
	(void)lexer;
	(void)env;
	str = ft_tstrjoin(str, token->value);
	str = ft_tstrjoin(str, ft_getchar(127));

	return (str);
}

char	*ft_getchar(char c)
{
	char	*str;

	str = malloc(2 * sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	is_redirection(token_t *token)
{
	if (token->type < 4 && token->type >= 0)
		return (1);
	return (0);
}

t_redir	*struct_redir(token_t *token, lexer_t *lexer, char **env)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	redir->next = NULL;
	if (token->type == token_herdoc)
		col_redir(redir, lexer, token, env);
	else if (token->type == token_apend)
		col_redir(redir, lexer, token, env);
	else if (token->type == token_infile)
		col_redir(redir, lexer, token, env);
	else if (token->type == token_outfile)
		col_redir(redir, lexer, token, env);
	return (redir);
}
