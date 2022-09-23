/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:56:56 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/23 18:53:08 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/shell.h"

int	ft_count_herdoc_pipes(t_cmd *command)
{
    t_cmd   *cmd;
    t_redirection *redirection;
    int     i;
	int		j;

    cmd = command;
	i = 0;
	j = 0;
    while (cmd)
    {
		j = 0;
        redirection = cmd->redirection;
        while (redirection)
        {
			if (j == 0)
			{
				if (ft_strcmp(cmd->redirection->type, "<<") == 0)
				{
					i++;
					j = 1;
				}
			}
            redirection= redirection->next;
        }
        cmd = cmd->next;
        printf("we are in next neaud\n");
    }
	return (i);
}

void    ft_check_her_doc(t_shell *shell, t_cmd *cmd)
{
    // t_cmd   *cmd;
    shell = NULL;
	int	k;
    char			*limiter;
    int				j;

	k = 0;
    k = ft_count_herdoc_pipes(cmd);
    // cmd = command;
    // printf("env[1] : %s\n", shell->env[1]);
    // printf("//%s\n", cmd->cmd[0]);
	printf("%d\n", k);
    while (cmd)
    {   
        while(cmd->redirection)
        { 
            printf("--%s\n", cmd->cmd[0]);
            while (1)
            {
                j = 1;
		    	write (1, ">", 1);
                limiter = get_next_line(0);
                j = ft_strncmp(limiter, cmd->redirection->value, \
		    		ft_strlen(limiter));
		        if (j)
		    	{
		    	    // write(1, limiter, ft_strlen(limiter));
                    // write (1, "\n", 1);
		    	}
		        else
		    	    break ;
            }
            cmd->redirection = cmd->redirection->next;
        }
        cmd = cmd->next;
    }

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

void    ft_get_exec(t_shell *shell, t_cmd *cmd) 
{   
    pid_t id;
    // redir = NULL;
    // shell = NULL;

    id = fork();
    // printf("ppppp : %s\n", cmd->redirection->value);
    if (id == 0)
        ft_check_her_doc(shell, cmd);
    else
        printf("--------------------cmd : %s\n", cmd->cmd[0]);
    wait(NULL);
    // ft_check_builtins(shell, cmd);
    exec(shell, cmd);
    // while (cmd)
    // int i = 0;
    // while (cmd)
    // {
    //      i = 0;
    //     while (cmd->cmd[i])
    //     {
    //         printf("cmd[%d] : %s\n", i, cmd->cmd[i]);
    //         i++;
    //     }
    //     cmd = cmd->next;
    // }
}