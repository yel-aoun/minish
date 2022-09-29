/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:27:46 by araysse           #+#    #+#             */
/*   Updated: 2022/09/29 12:52:15 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	ft_free_struct(t_cmd **cmd)
{
	int i;
	t_cmd *com;
	
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

void	ft_free2(t_redirection **redir)
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

void	pr_struct(t_cmd *str)
{
	int i;
	t_cmd*	cmd;
	
	cmd = str;
	i = 0;
	while (cmd)
	{
		i = 0;
		printf("########  STRUCT  ######\n");
		while (cmd->cmd[i])
		{
			printf(" ---cmd[%d]--->   %s\n",i, cmd->cmd[i]);
			i++;
		}
		printf("infile : %d\n", cmd->infile);
		printf("outfile : %d\n", cmd->outfile);
		while (cmd->redirection)
		{
			printf("redirection : %s\n", cmd->redirection->type);
			printf("redirection : %s\n", cmd->redirection->value);
			cmd->redirection = cmd->redirection->next;
		}
		cmd =cmd->next;
	}
	printf("nanannanananaanan \n");
}

void	ppp_struct(t_redirection *str)
{
	int i;
	t_redirection*	redir;
	
	redir = str;
	i = 0;
	while (redir)
	{
		printf("########  STRUCT  ######\n");
		printf("neud n:%d type : %s, value : %s\n", i, redir->type, redir->value);
		redir =redir->next;
		i++;
	}
	printf("nonoonoonoonono \n");
}


void collect_redirection(t_redirection *redir, lexer_t *lexer, token_t *token, char **env)
{
	token_t	*tok1;
	lexer_t	*lexer1;
	int		i;
	
	i = 0;
	lexer1 = init_lexer(lexer->contents);
	while (lexer1->i < lexer->i)
		tok1 = lexer_get_next_token(lexer1, env);
	tok1 = lexer_get_next_token(lexer1, env);
	redir->type = token->value;
	// printf(" tok1 next : %s\n", tok1->value);
	if (tok1 == NULL)
		redir->value = NULL;
	else if (tok1->type != token_word)
		redir->value = NULL;
	else if (tok1->type == token_word)
	{
		redir->value = tok1->value;
		token = lexer_get_next_token(lexer, env);
	}
	// token = lexer_get_next_token(lexer, env);
	// printf(" token next : %s\n", token->value);
}

char	*struct_cmd(lexer_t *lexer, token_t *token, char *str, char **env)
{
	(void)lexer;
	(void)env;
	// if (str[0] == '\0')
	// 	return (str);
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

t_redirection	*struct_redir(token_t *token, lexer_t *lexer, char **env)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	redir->next = NULL;
	
	if (token->type == token_herdoc)
		collect_redirection(redir, lexer, token, env);
	else if (token->type == token_apend)
		collect_redirection(redir, lexer, token, env);
	else if (token->type == token_infile)
		collect_redirection(redir, lexer, token, env);
	else if (token->type == token_outfile)
		collect_redirection(redir, lexer, token, env);
	return (redir);
}

void	ft_sig_int(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_exit_sig(char *str)
{
	printf("%s\n", str);
	exit(0);
}

int main(int ac, char **av, char **env)
{
	t_shell	*shell;
	char    *inpt;
	char	*str;
	t_redirection	*redir;
	// t_redirection	*newr;
	t_cmd	*cmd;
	t_cmd	*new;
	token_t *token = (void*)0;

	cmd = NULL;
	shell = malloc(sizeof(t_shell));
	ft_init_env(shell, env);
	while(1)
	{
		str = NULL;
		signal(SIGINT, ft_sig_int);
		signal(SIGQUIT, SIG_IGN);
        inpt = readline(YELLOW "bash-0.0 " WHITE);
		if (!inpt)
			ft_exit_sig("exit");
		if (ft_strcmp(inpt, ""))
		{
        	add_history(inpt);
			redir = NULL;
			lexer_t *lexer = init_lexer(inpt);
			
			(void) (ac);
			(void) (av);
			while ((token = lexer_get_next_token(lexer, shell->env )) != NULL)
			{
				// printf("ssstttrrrr,main : %s\n", token->value);
				while (token->type != token_pipe)
				{
					if (is_redirection(token))
					{
						ft_lstadd_bak(&redir, struct_redir(token, lexer, shell->env));
					}
					else
						str = struct_cmd(lexer, token, str, shell->env);
					if ((token = lexer_get_next_token(lexer, shell->env)) == NULL)
						break;
				}
				// ppp_struct(redir);
				ft_lstnew(&new, redir, str);
				new->next = NULL;
				ft_lstadd_back(&cmd, new);
				redir = NULL;
				str = NULL;
			}
			pr_struct(cmd);
			// ft_get_exec(shell, cmd);
			ft_free_struct(&cmd);
			free (str);
		}
	}
}
	