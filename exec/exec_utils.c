/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 08:57:45 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/16 17:33:27 by yel-aoun         ###   ########.fr       */
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
	save = ft_substr(env[i], 5, ft_strlen(env[i]) - 5);
	path = ft_split(save, ':');
	i = 0;
	while (path && path[i])
	{
		path[i] = ft_strjoin_2(path[i], "/");
		i++;
	}
	free(save);
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
	if (cmd[0][0] == '\0')
		ft_err_cmd(cmd[0], 1);
	else
		ft_help_get_cmd(shell, cmd);
}
