/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:44:12 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/29 18:40:57 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_help_count(char *str1, char *str)
{
	char	**splt;
	// int		k;

	// k = 0;
	splt = ft_split(str1, '=');
	if (!ft_strncmp(splt[0], str, ft_strlen(str)) && ft_strlen(str) == ft_strlen(splt[0]))
		return (1);
	else
		return (0);
	// k = ft_is_longer(splt[0], str);
	// return (k);
}

char	**update_env(t_shell *shell, char *str)
{
	int		i;
	int		j;
	int		k;
	char	**env;

	i = 0;
	j = 0;
	k = 0;
	env = malloc(sizeof(char *) * (ft_count(shell->env) + 1));
	while (shell->env[j])
	{
		// k = ft_help_count(shell->export[j], str);
		// if (ft_strncmp(shell->env[j], str, k) == 0)
			// j++;
		if (!ft_help_count(shell->env[j], str))
		{
			env[i] = ft_strdup(shell->env[j]);
			i++;
		}
		j++;
	}
	env[i] = NULL;
	return (env);
}

char	**update_export(t_shell *shell, char *str)
{
	char	**export;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	export = malloc(sizeof(char *) * (ft_count(shell->export) + 1));
	while (shell->export[j])
	{
		// k = ft_help_count(shell->export[j], str);
		// if (ft_strncmp((shell->export[j]), str, k) == 0)
		// 	j++;
		if (!ft_help_count(shell->export[j], str))
		{
			export[i] = ft_strdup(shell->export[j]);
			i++;
		}
		j++;
	}
	export[i] = NULL;
	return (export);
}

int	ft_unset(t_shell *shell, t_cmd *cmd)
{
	int i;

	i = 0;
	if (!cmd->cmd[1])
		return (1);
	while (cmd->cmd[i])
	{
		shell->env = update_env(shell, cmd->cmd[i]);
		shell->export = update_export(shell, cmd->cmd[i]);
		i++;
	}
	g_glob[1] = 0;
	return (1);
}