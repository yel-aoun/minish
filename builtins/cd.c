/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 09:42:21 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/15 12:21:38 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../includes/shell.h"

void	ft_norm(t_shell *shell)
{
	shell->env = ft_oldpwd(shell->env);
	shell->env = ft_pwd(shell->env);
	shell->export = ft_oldpwd(shell->export);
	shell->export = ft_pwd(shell->export);
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

void	ft_cd_help(t_shell *shell)
{
	char	*tmp;
	char	**splt;

	if (shell->cmd_args[1][0] == '~')
	{
		tmp = ft_find(shell->env, "HOME");
		if (tmp != NULL)
		{
			splt = ft_split(tmp, '=');
			if (chdir(splt[1]) == -1)
				printf("cd: %s: No such file or directory\n", \
					shell->cmd_args[1]);
			else
				ft_norm(shell);
		}
	}
	else if (chdir(shell->cmd_args[1]) == -1)
		printf("cd: %s: No such file or directory\n", shell->cmd_args[1]);
	else
		ft_norm(shell);
}

void	ft_cd(t_shell *shell)
{
	char	*tmp;
	char	**splt;

	if (shell->cmd_args[1] != NULL)
		ft_cd_help(shell);
	else
	{
		tmp = ft_find(shell->env, "HOME");
		if (tmp != NULL)
		{
			splt = ft_split(tmp, '=');
			if (chdir(splt[1]) == -1)
				printf("cd: %s: No such file or directory\n", \
					shell->cmd_args[1]);
			else
				ft_norm(shell);
		}
	}
}
