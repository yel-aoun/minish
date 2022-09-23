/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:56:56 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/23 12:18:46 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/shell.h"

void    ft_check_her_doc(t_shell *shell, t_cmd *cmd)
{
    // t_cmd*	redir;
    // char			*limiter;
    // int				j;

	// redir = red;
    printf("env[0] : %s\n", shell->env[0]);
    // while (cmd)
    // {
        // cmd = cmd->next;
        // cmd = cmd->next;
        while (cmd->redirection)
        {
            printf("cmd->red->type : %s\n", cmd->redirection->type);
            printf("cmd->red->value : %s\n", cmd->redirection->value);
            printf("___________\n");
            cmd->redirection = cmd->redirection->next;
        }
    //     printf("we are in next neaud\n");
    // }
    // while (redir)
    // {
    //     while (1)
    //     {
    //         j = 1;
	// 		write (1, ">", 1);
    //         limiter = get_next_line(0);
    //         j = ft_strncmp(limiter, cmd->redir->value, \
	// 			ft_strlen(limiter));
	// 	    if (j)
	// 		{
	// 		    write(1, limiter, ft_strlen(limiter));
    //             write (1, "\n", 1);
	// 		}
	// 	    else
	// 		    break ;
    //     }
    //     redir = redir->next;
    // }

    // i = 1;
    //     write (1, "> ", 2);
    //     lim = get_next_line(0);
    //     i = ft_strncmp(lim, pipex->limiter, ft_strlen(pipex->limiter));
    //     if (i)
    //         write (pipex->heredoc_pip[1], lim, ft_strlen(lim));
    //     else
    //         break ;
        // printf("type : %s\n", redir->type);
        // printf("value : %s\n", redir->value);
}

void    ft_get_exec(t_shell *shell, t_cmd *cmd, t_redirection *redir)
{   
    // pid_t id;
    redir = NULL;
    // shell = NULL;

    // id = fork();
    // printf("ppppp : %s\n", redir->value);
    // if (id == 0)
    //     ft_check_her_doc(shell, cmd);
    // else
    //     printf("cmd : %s\n", cmd->cmd[0]);
    // // ft_check_builtins(shell, cmd);
    // wait(NULL);
    exec(shell, cmd);
    // while (cmd)
    // {
    //     printf("cmd : %s\n", cmd->cmd[0]);
    //     cmd = cmd->next;
    // }
}