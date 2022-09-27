/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 13:56:56 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/27 17:55:34 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/shell.h"

void	ft_help_print_err_fille(char *err)
{
	write (2, "bash: ", 6);
	write (2, err, ft_strlen(err));
	write (2, ":", 1);
}

void	ft_check_access(char *arg, int n, t_shell *shell)
{
	if (n == 0)
	{
		if (access(arg, R_OK) == -1)
		{
			ft_help_print_err_fille(arg);
			perror("");
			exit(1);
		}
	}
	if (n == 1)
	{
		if (access(arg, W_OK) == -1)
		{
			ft_help_print_err_fille(arg);
			perror("");
			shell->exit_creat = 1;
		}
	}
	if (n == 2)
	{
		if (access(arg, F_OK) == -1)
		{
			ft_help_print_err_fille(arg);
			perror("");
			exit(1);
		}
	}
}

void	ft_open(int flags, char *filename, t_shell *shell)
{
	int	i;

	i = 0;
	// printf("ima heeer with flage %d\n", flags);
	// printf("ima heeer with file %s\n", filename);
	if (flags == 1)
	{
		ft_check_access(filename, 2, shell);
		ft_check_access(filename, 0, shell);
		if (shell->exit_creat == 1)
			return ;
		i = open(filename, O_RDWR);
	}
	else if (flags == 2)
	{
		i = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
		ft_check_access(filename, 2, shell);
		ft_check_access(filename, 1, shell);
	}
	else if (flags == 3)
	{
		i = open(filename, O_CREAT | O_RDWR | O_APPEND, 0600);
		ft_check_access(filename, 2, shell);
		ft_check_access(filename, 1, shell);
	}
}

void	ft_open_files(t_shell *shell, t_cmd *command)
{
	int 			i;
	t_cmd			*cmd;
	t_redirection	*redirection;

	i = 0;
	shell->exit_creat = 0;
	cmd = command;
	while (cmd)
	{
		// printf("checkk\n");
		shell->exit_creat = 0;
		redirection = cmd->redirection;
		while(redirection)
		{
			if(ft_strcmp(redirection->type, "<") == 0)
				ft_open(1, redirection->value, shell);
			else if(ft_strcmp(redirection->type, ">") == 0)
				ft_open(2, redirection->value, shell);
			else if(ft_strcmp(redirection->type, ">>") == 0)
				ft_open(3, redirection->value, shell);
			if (shell->exit_creat == 1)
				break;
			else
				redirection = redirection->next;
		}
		cmd = cmd->next;
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
				if (ft_strcmp(redirection->type, "<<") == 0)
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
		i++;
	}
}
void	ft_open_heredoc(t_shell *shell, t_redirection *redirection, int i)
{
	int		j;
	char	*limiter;

	j = 0;
	close(shell->pip_herdoc[i][0]);
	while (1)
	{
	    j = 1;
	    limiter = readline("> ");
	    j = ft_strncmp(limiter, redirection->value, \
	        ft_is_longer(limiter, redirection->value));
	    if (j)
		{
		    write(shell->pip_herdoc[i][1], limiter, ft_strlen(limiter));
	        write(shell->pip_herdoc[i][1], "\n", 1);
		}
	    else
		    break ;
	}
}

void    ft_check_her_doc(t_shell *shell, t_cmd *command, int k)
{
    t_cmd   *cmd;
	t_redirection *redirection;
	pid_t	id;
	int		i;
	int		new_neud;

	cmd = command;
	k = 0;
	i = -1;
	new_neud = 0;
    while (cmd)
    {
		redirection = cmd->redirection;
		if (redirection)
			new_neud = 1;
        while(redirection)
        {
			if (ft_strcmp(redirection->type, "<<") == 0)
			{
				if (new_neud == 1)
				{
					i++;
					new_neud = 0;
				}
				if (redirection->value == NULL)
					break;
				pipe(shell->pip_herdoc[i]);
				// pipe(cmd->fd);
				id = fork();
    			if (id == 0)
				{
					ft_open_heredoc(shell, redirection, i);
					exit (0);
				}
				else
       				wait(NULL);	
			cmd->infile = shell->pip_herdoc[i][0];
			cmd->outfile = shell->pip_herdoc[i][1];
			// printf("%d\n", cmd->infile);
			// printf("%d\n", cmd->outfile);
			}
            redirection = redirection->next;
        }
		new_neud = 0;
        cmd = cmd->next;
    }
	cmd = command;
	redirection = cmd->redirection;
	// ft_open_files(shell, cmd);
	// cmd->infile = shell->pip_herdoc[0][0];
	// cmd->outfile = shell->pip_herdoc[0][1];
	// close (cmd->outfile);
}
// void    ft_open_files(t_shell *shell, t_cmd *cmd)
// {
    
// }

void    ft_get_exec(t_shell *shell, t_cmd *cmd) 
{   
	int	k;

	k = 0;
	k = ft_count_herdoc_pipes(cmd);
	ft_create_pipes_heredoc(shell, k);
    ft_check_her_doc(shell, cmd, k);
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