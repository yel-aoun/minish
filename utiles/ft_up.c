/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_up.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 12:23:22 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/07 10:20:40 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*ft_join(char *add, char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			break ;
		i++;
	}
	if (add[i] == '=')
		new = ft_strjoin(add, (str + (i + 2)));
	else
	{
		new = ft_strjoin(add, "=");
		new = ft_strjoin(new, (str + (i + 2)));
	}
	return (new);
}

char	**ft_join_env(t_shell *shell, char *str)
{
	char	**env;
	char	**splt;
	char	**s_p;
	char	**splt_shell;

	shell->i = 0;
	shell->k = 0;
	s_p = ft_split(str, '=');
	splt = ft_split(s_p[0], '+');
	ft_free(s_p);
	env = malloc(sizeof(char *) * (ft_count(shell->env) + 1));
	while (shell->env[shell->i])
	{
		splt_shell = ft_split(shell->env[shell->i], '=');
		shell->k = ft_is_longer(splt_shell[0], splt[0]);
		if (ft_strncmp(splt_shell[0], splt[0], shell->k) == 0)
			env[shell->i] = ft_join(shell->env[shell->i], str);
		else
			env[shell->i] = ft_strdup(shell->env[shell->i]);
		shell->i++;
		ft_free (splt_shell);
	}
	env[shell->i] = NULL;
	ft_free(splt);
	return (env);
}

char	**ft_join_export(t_shell *shell, char *str)
{
	char	**export;
	char	**splt;
	char	**s_p;
	char	**splt_shell;

	shell->i = 0;
	shell->k = 0;
	s_p = ft_split(str, '=');
	splt = ft_split(s_p[0], '+');
	export = malloc(sizeof(char *) * (ft_count(shell->export) + 1));
	while (shell->export[shell->i])
	{
		splt_shell = ft_split(shell->export[shell->i], '=');
		shell->k = ft_is_longer(splt_shell[0], splt[0]);
		if (ft_strncmp(splt_shell[0], splt[0], shell->k) == 0)
			export[shell->i] = ft_join(shell->export[shell->i], str);
		else
			export[shell->i] = ft_strdup(shell->export[shell->i]);
		shell->i++;
		ft_free (splt_shell);
	}
	export[shell->i] = NULL;
	ft_free(s_p);
	ft_free(splt);
	return (export);
}

char	**ft_up_env(t_shell *shell, char *str)
{
	int		i;
	char	**env;
	char	**splt;
	char	*tmp;

	i = 0;
	splt = ft_split(str, '=');
	tmp = ft_strjoin(splt[0], "=");
	env = malloc(sizeof(char *) * (ft_count(shell->env) + 2));
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], tmp, strlen(tmp)) == 0)
			env[i] = ft_strdup(str);
		else
			env[i] = ft_strdup(shell->env[i]);
		i++;
	}
	env[i] = NULL;
	ft_free(splt);
	free(tmp);
	return (env);
}

char	**ft_up_export(t_shell *shell, char *str)
{
	char	**export;
	int		i;
	int		k;
	char	**splt;
	char	**splt_shell;

	i = 0;
	k = 0;
	splt = ft_split(str, '=');
	export = malloc(sizeof(char *) * (ft_count(shell->export) + 1));
	while (shell->export[i])
	{
		splt_shell = ft_split(shell->export[i], '=');
		k = ft_is_longer(splt_shell[0], splt[0]);
		if (ft_strncmp(splt_shell[0], splt[0], k) == 0)
			export[i] = ft_strdup(str);
		else
			export[i] = ft_strdup(shell->export[i]);
		i++;
		ft_free (splt_shell);
	}
	export[i] = NULL;
	ft_free(splt);
	return (export);
}
