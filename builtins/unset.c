/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 09:44:12 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/04 15:03:00 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_help_count(char *str1, char *str)
{
	char	**splt;

	splt = ft_split(str1, '=');
	if (!ft_strncmp(splt[0], str, ft_strlen(str)) && \
		ft_strlen(str) == ft_strlen(splt[0]))
		return (1);
	else
		return (0);
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
	int	i;
	int	k;

	i = 0;
	k = 0;
	if (!cmd->cmd[1])
	{
		g_glob[1] = 0;
		return (1);
	}
	while (cmd->cmd[i])
	{
		if (ft_valid_unset(cmd->cmd[i]))
			ft_valide_unset(shell, cmd, i);
		else
		{
			printf("bash: unset: `%s': not a valid identifier\n", cmd->cmd[i]);
			g_glob[1] = 1;
			k = 1;
		}
		i++;
	}
	if (k == 1)
		g_glob[1] = 1;
	return (1);
}
