/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_main1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:57:43 by araysse           #+#    #+#             */
/*   Updated: 2022/10/04 18:01:41 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_after_pipe1(lexer_t *lexer, token_t *token, char **env)
{
	token_t	*tok3;
	lexer_t	*lexer3;

	lexer3 = init_lexer(lexer->contents);
	tok3 = lexer_next(lexer3, env);
	if (token)
	{
		if (tok3->type == token_pipe)
		{
			printf("bash: syntax error near unexpected token `|'\n");
			g_glob[0] = 1;
			g_glob[1] = 258;
			return (1);
		}
		return (0);
	}
	return (0);
}

void	ft_after_pipe(lexer_t *lexer, token_t *token, char **env)
{
	token_t	*tok2;
	lexer_t	*lexer2;
	int		i;

	if (ft_after_pipe1(lexer, token, env) == 1)
		return ;
	i = 0;
	lexer2 = init_lexer(lexer->contents);
	while (lexer2->i < lexer->i)
		tok2 = lexer_next(lexer2, env);
	if (token != NULL)
	{
		tok2 = lexer_next(lexer2, env);
		if (token->type == token_pipe && (tok2 == NULL))
		{
			printf("bash: syntax error near unexpected token `|'\n");
			g_glob[0] = 1;
			g_glob[1] = 258;
		}
	}
}

void	ft_free_struct(t_cmd **cmd)
{
	int		i;
	t_cmd	*com;

	com = *cmd;
	i = 0;
	while ((*cmd))
	{
		i = 0;
		while ((*cmd)->cmd[i])
		{
			free((*cmd)->cmd[i]);
			i++;
		}
		free((*cmd)->cmd);
		(*cmd) = (*cmd)->next;
	}
	free((*cmd));
}

void	ft_free2(t_redir **redir)
{
	int		i;

	i = 0;
	while (*redir)
	{
		free((*redir)->type);
		free((*redir)->value);
		(*redir) = (*redir)->next;
	}
	free ((*redir));
}
