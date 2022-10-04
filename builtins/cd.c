/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:42:21 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/02 11:28:19 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_norm(t_shell *shell)
{
	shell->pwd = getcwd(NULL, 0);
	if (shell->pwd)
	{
		shell->env = ft_oldpwd(shell->env);
		shell->env = ft_pwd(shell->env);
		shell->export = ft_oldpwd(shell->export);
		shell->export = ft_pwd(shell->export);
	}
	g_glob[1] = 0;
}

char	*ft_find(char **new, char *find)
{
	int		i;
	int		k;
	char	**splt;

	k = 0;
	i = 0;
	while (new[i])
	{
		splt = ft_split(new[i], '=');
		k = ft_is_longer(splt[0], find);
		if (k > 0)
		{
			if (ft_strncmp(splt[0], find, k) == 0)
			{
				free (splt);
				return (new[i]);
			}
			i++;
		}
		else
			i++;
		free (splt);
	}
	return (NULL);
}

void	ft_cd_more_help(char *tmp, t_shell *shell, char *cmd)
{
	char	**splt;

	splt = ft_split(tmp, '=');
	if (chdir(splt[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd);
		g_glob[1] = 1;
	}
	else
		ft_norm(shell);
	free(splt);
}

void	ft_cd_help(t_shell *shell, t_cmd *cmd)
{
	char	*tmp;

	if (cmd->cmd[1][0] == '~')
	{
		tmp = ft_find(shell->env, "HOME");
		if (tmp != NULL)
			ft_cd_more_help(tmp, shell, cmd->cmd[1]);
		free(tmp);
	}
	else if (chdir(cmd->cmd[1]) == -1)
	{
		printf("cd: %s: No such file or directory\n", cmd->cmd[1]);
		g_glob[1] = 1;
	}
	else
		ft_norm(shell);
}

int	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*tmp;
	char	**splt;

	shell->pwd = NULL;
	if (cmd->cmd[1] != NULL)
		ft_cd_help(shell, cmd);
	else
	{
		tmp = ft_find(shell->env, "HOME");
		if (tmp != NULL)
		{
			splt = ft_split(tmp, '=');
			if (chdir(splt[1]) == -1)
			{
				printf("cd: %s: No such file or directory\n", \
					shell->cmd_args[1]);
				g_glob[1] = 1;
			}
			else
				ft_norm(shell);
			free(splt);
		}
		free(tmp);
	}
	return (1);
}
