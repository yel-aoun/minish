/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:34:42 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/20 15:50:26 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	ft_count(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	*ft_find_in_env(char **new, char *find)
{
	int	i;

	i = 0;
	while (new[i])
	{
		if (strncmp(new[i], find, strlen(find)) == 0)
			return (new[i]);
		i++;
	}
	return (NULL);
}

void	ft_export(t_shell *shell, char **env)
{
	int		i;
	// char	**export;

	i = 0;
	shell->export = malloc(sizeof(char *) * ft_count(env) + 1);
	if (!shell->export)
		return ;
	while (env[i])
	{
		shell->export[i] = ft_strdup(env[i]);
		i++;
	}
	shell->export[i] = NULL;
}

void	ft_env(t_shell *shell, char **env)
{
	int		i;
	// char	**new;

	i = 0;
	shell->env = malloc(sizeof(char *) * ft_count(env) + 1);
	if (!shell->env)
		return ;
	while (env[i])
	{
		shell->env[i] = ft_strdup(env[i]);
		i++;
	}
	shell->env[i] = NULL;
}
