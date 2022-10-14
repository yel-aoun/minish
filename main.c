/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 11:27:46 by araysse           #+#    #+#             */
/*   Updated: 2022/10/14 11:47:41 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/shell.h"

void	pr_struct(t_cmd *str)
{
	int		i;
	t_cmd	*cmd;

	cmd = str;
	i = 0;
	printf("-----%so--\n", cmd->cmd[0]);
	while (cmd)
	{
		i = 0;
		printf("########  STRUCT  ######\n");
		// if (cmd->cmd)
		// {	
		while (cmd->cmd[i])
			{
				printf(" ---cmd[%d]--->   %s\n", i, cmd->cmd[i]);
				i++;
			}
		// }
		printf("infile : %d\n", cmd->infile);
		printf("outfile : %d\n", cmd->outfile);
		while (cmd->redirection)
		{
			printf("redirection : %s\n", cmd->redirection->type);
			printf("redirection : %s\n", cmd->redirection->value);
			cmd->redirection = cmd->redirection->next;
		}
		cmd = cmd->next;
	}
	printf("nanannanananaanan \n");
}

void	function(t_cmd **cmd, t_lexer **lexer, char **env, t_token **token)
{
	char	*str;
	t_cmd	*new;
	t_redir	*redir;

	redir = NULL;
	str = NULL;
	new = NULL;
	while ((*token)->e_type != token_pipe)
	{
		if (is_redirection(*token))
			ft_lstadd_bak(&redir, struct_redir((*token), (*lexer), env));
		else
			str = struct_cmd((*lexer), (*token), str, env);
		free (*token);
		(*token) = lexer_next((*lexer), env, 1);
		if ((*token) == NULL)
			break ;
	}
	if (g_glob[2] == 0)
		ft_after_pipe(lexer, (*token), env);
	ft_lstnew(&new, redir, str);
	ft_lstadd_back(cmd, new);
	new->next = NULL;
	free(str);
}

void	ft_help_main2(t_cmd **cmd, t_lexer **lexer, char **env)
{
	t_token	*token;

	token = NULL;
	g_glob[2] = 0;
	token = lexer_next((*lexer), env, 1);
	while (token != NULL)
	{
		function(cmd, lexer, env, &token);
		if (token)
		{
			free(token->value);
			free(token);
		}
		token = lexer_next((*lexer), env, 1);
	}
}

void	ft_help_main1(t_cmd **cmd, t_shell *shell)
{
	char	*inpt;
	t_lexer	*lexer;

	lexer = NULL;
	inpt = readline(YELLOW "bash-0.0 " WHITE);
	if (!inpt)
	{
		g_glob[1] = 0;
		ft_exit_sig("exit");
	}
	if (ft_strcmp(inpt, ""))
	{
		add_history(inpt);
		lexer = init_lexer(inpt);
		ft_help_main2(cmd, &lexer, shell->env);
		free(lexer->contents);
		free(lexer);
		if (g_glob[0] == 0)
			ft_get_exec(shell, (*cmd));
		// pr_struct(*cmd);
		ft_free_struct(cmd);
	}
	else
		free(inpt);
}

int	main(int ac, char **av, char **env)
{
	t_shell	*shell;
	t_cmd	*cmd;

	(void)(ac);
	(void)(av);
	g_glob[2] = 0;
	cmd = NULL;
	shell = malloc(sizeof(t_shell));
	ft_init_env(shell, env);
	g_glob[1] = 0;
	while (1)
	{
		g_glob[0] = 0;
		signal(SIGINT, ft_sig_int);
		signal(SIGQUIT, SIG_IGN);
		ft_help_main1(&cmd, shell);
	}
}
