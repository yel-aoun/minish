/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:57:45 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/24 18:59:34 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	**ft_get_path(char **env)
{
	char	**path;
	char	*save;
	int		i;

	i = 0;
	path = NULL;
	save = NULL;
	while (env[i])
	{
		if (!ft_strncmp (env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (env[i])
		save = ft_substr(env[i], 5, ft_strlen(env[i] + 5));
	path = ft_split(save, ':');
	i = 0;
	while (path && path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	return (path);
}

int	command_with_path(t_shell *shell, char **command)
{
	char	*path;
	int		check;

	check = 1;
	path = ft_strchr(command[0], '/');
	if (path)
	{
		check = access(command[0], X_OK);
		if (!check)
			shell->command_path = command[0];
	}
	return (check);
}

int	command_without_path(t_shell *shell, char **command)
{
	int		j;
	char	*path;
	int		check;

	j = 0;
	check = 0;
	while (shell->path[j])
	{
		path = ft_strjoin(shell->path[j], command[0]);
		check = access(path, X_OK);
		if (!check)
		{
			shell->command_path = path;
			break ;
		}
		free(path);
		j++;
	}
	return (check);
}

void	ft_get_cmd(t_shell *shell, char **cmd)
{
	int		check;
	char	**command;

	command = ft_split(cmd[0], ' ');
	shell->path = ft_get_path(shell->env);
	if (shell->path)
	{
		check = command_with_path(shell, command);
		if (check == -1)
		    ft_err_cmd(cmd[0], 2);
		if (check == 1)
		{
			check = command_without_path(shell, cmd);
			if (check == -1)
				ft_err_cmd(cmd[0], 1);;
	    }
	}
	else
		ft_err_cmd(cmd[0], 2);
}
