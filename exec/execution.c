/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:52:47 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/29 10:36:49 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

// typedef struct s_exe
// {
// 	char	**cmd;
// }		t_exe;

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
			shell->exit_creat = 1;
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
			shell->exit_creat = 1;
		}
	}
}

void	ft_open(int flags, char *filename, t_shell *shell)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (flags == 1)
	{
		ft_check_access(filename, 2, shell);
		if (shell->exit_creat == 1)
			return ;
		ft_check_access(filename, 0, shell);
		if (shell->exit_creat == 1)
			return ;
		// fprintf(stderr, "hnaaaa\n");
		i = open(filename, O_RDWR, 0644);
		shell->in = 1;
		dup2(i, 0);
	}
	else if (flags == 2)
	{
		i = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
		ft_check_access(filename, 2, shell);
		if (shell->exit_creat == 1)
			return ;
		ft_check_access(filename, 1, shell);
		if (shell->exit_creat == 1)
			return ;
		shell->out = 1;
		dup2(i, 1);
	}
	else if (flags == 3)
	{
		i = open(filename, O_CREAT | O_RDWR | O_APPEND, 0644);
		ft_check_access(filename, 2, shell);
		if (shell->exit_creat == 1)
			return ;
		ft_check_access(filename, 1, shell);
		if (shell->exit_creat == 1)
			return ;
		shell->out = 1;
		dup2(i, 1);
	}
}

void	ft_open_files(t_shell *shell, t_cmd *command)
{
	int 			i;
	t_cmd			*cmd;
	t_redirection	*redirection;

	i = 0;
	shell->exit_creat = 0;
	shell->in = 0;
	shell->out = 0;
	cmd = command;
	redirection = cmd->redirection;
	while(redirection)
	{
		if (ft_strcmp(redirection->type, "<<") == 0)
		{
			shell->in = 1;
			dup2(cmd->infile, 0);
			close(cmd->outfile);
		}
		else if(ft_strcmp(redirection->type, "<") == 0)
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
}

void	ft_close_files(t_cmd *command)
{
	t_cmd *cmd;
	t_redirection *redirection;

	cmd = command;
	while (cmd)
	{	redirection = cmd->redirection;
		while (redirection)
		{
			if (ft_strcmp(redirection->type, "<<") == 0)
			{
				close(cmd->infile);
				close(cmd->outfile);
			}
			redirection = redirection->next;
		}
		cmd = cmd->next;
	}
}

void	ft_close(t_shell *shell, int k)
{
	int	i;

	i = 0;
	while (i < k)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
}

int	co_unt(t_cmd *cmd)
{
	int	i;
	t_cmd *count;

	i = 0;
	count = cmd;
	while (count->next)
	{
		count = count->next;
		i++;
	}
	return (i);
}

void	ex_betw(t_shell *shell, t_cmd *command, int k)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = command;
	cmd = cmd->next;
	while (i < k - 1)
	{
		pipe(shell->pipes[i + 1]);
		between_c(cmd, shell, i);
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
		cmd = cmd->next;
	}
}

void	execute_cmds(t_cmd *command, t_shell *shell, int k)
{
	int		i;
	pid_t	pid;
	pid_t	pid2;
	t_cmd	*cmd;
	// t_cmd	*cmd;

	i = 0;
	cmd = command;
	ft_creat_pipes(shell, k);
	pid = fork();
	if (pid == -1)
	{
		printf("bash: fork: Resource temporarily unavailable\n");
		return ;
	}
	if (pid == 0)
	{
		ft_open_files(shell, cmd);
		if (shell->exit_creat == 0)
			first_c(cmd, shell, k);
		else
			exit (1);
	}
	else
	{
		if (k > 0)
		{
			ex_betw(shell, cmd, k);
			pid2 = fork();
			if (pid2 == 0)
			{
				while (cmd->next)
				{
					cmd = cmd->next;
				}
				ft_open_files(shell, cmd);
				if (shell->exit_creat == 0)
				{
					last_c(cmd, shell, k - 1);
					fprintf(stderr,"heeeeeer\n");
				}
				else
					exit(0);
			}
			else
			{
				cmd = command;
				ft_close(shell, k);
				// ft_close_files(cmd);
			}
		}
		while (wait(NULL) != -1)
		{
		}
	}
}

void	exec(t_shell *shell, t_cmd *cmd)
{
	int	k;
	int	l;

	l = 0;
	k = co_unt(cmd);
	if (k == 0)
	{
		l = ft_check_builtins(shell, cmd);
		if (l == 0)
			execute_cmds(cmd, shell, k);
	}
	else
		execute_cmds(cmd, shell, k);
}
