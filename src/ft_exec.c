/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:56:56 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/24 10:09:14 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/shell.h"

void    ft_create_pipes_heredoc(t_shell *shell, int k)
{
	int	i;

	i = 0;
	shell->pip_herdoc = malloc(sizeof(int *) * k);
	if (!shell->pip_herdoc)
		return ;
	while (i < k)
	{
		shell->pip_herdoc[i] = malloc(sizeof(int) * 2);
		pipe(shell->pip_herdoc[i]);
		i++;
	}
}

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
    ft_create_pipes_heredoc(shell, k);
    while (cmd)
    {   
        while(cmd->redirection)
        { 
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
    exit (0);
}

void    ft_get_exec(t_shell *shell, t_cmd *cmd) 
{   
    // pid_t id;
    // // redir = NULL;
    // // shell = NULL;

    // id = fork();
    // // printf("ppppp : %s\n", cmd->redirection->value);
    // if (id == 0)
    //     ft_check_her_doc(shell, cmd);
    // else
    //     wait(NULL);
	// cmd = cmd->next;
	// printf("%s\n", cmd->cmd[0]);
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