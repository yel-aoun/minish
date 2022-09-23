/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:27:46 by araysse           #+#    #+#             */
/*   Updated: 2022/09/23 17:50:30 by yel-aoun         ###   ########.fr       */
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
	redir->type = token->value;
	redir->value = (lexer_get_next_token(lexer, env))->value;
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
        inpt = readline(YELLOW "minishell> " WHITE);
		if (ft_strcmp(inpt, ""))
		{
        	add_history(inpt);
			redir = NULL;
			lexer_t *lexer = init_lexer(inpt);
			
			(void) (ac);
			(void) (av);
			while ((token = lexer_get_next_token(lexer, shell->env )) != NULL)
			{
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
			// pr_struct(cmd);
			// printf("%s\n", cmd->cmd[0]);
			// while (cmd)
    		// {
    		//     while (cmd->redirection)
    		//     {
    		//         printf("cmd->red->type : %s\n", cmd->redirection->type);
    		//         printf("cmd->red->value : %s\n", cmd->redirection->value);
    		//         // printf("heeer\n");
    		//         printf("___________\n");
    		//         cmd->redirection = cmd->redirection->next;
    		//     }
    		//     cmd = cmd->next;
    		//     printf("we are in next neaud\n");
    		// }
			ft_get_exec(shell, cmd);
			ft_free_struct(&cmd);
			free (str); 
		}
	}
}



	