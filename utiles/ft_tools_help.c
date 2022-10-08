/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 18:02:14 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/08 17:50:04 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*ft_add(char *str)
{
	int		i;
	char	**splt;
	char	**sp;
	char	*new;

	i = 0;
	sp = ft_split(str, '=');
	splt = ft_split(sp[0], '+');
	while (sp[0][i] && sp[0][i] != '+')
		i++;
	new = ft_strjoin(splt[0], (str + (i + 1)));
	ft_free (sp);
	ft_free (splt);
	return (new);
}

int	ft_is_longer(char *str, char *str1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str || !str1)
		return (0);
	while (str[i])
		i++;
	while (str1[j])
		j++;
	if (j > i)
		return (j);
	else
		return (i);
}

char	**ft_add_env_help(char **env, char *str)
{
	int		b;
	char	**s_s;
	int		i;
	char	**new;

	i = 0;
	new = malloc(sizeof(char *) * (ft_count(env) + 2));
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	s_s = ft_split(str, '=');
	b = ft_search(s_s[0], '+');
	if (b == 1)
		new[i] = ft_add(str);
	else
		new[i] = ft_strdup(str);
	new[++i] = NULL;
	ft_free(s_s);
	return (new);
}

char	**ft_add_export_help1(t_shell *shell, char *splt, char *str)
{
	int		k;
	int		l;
	char	**new;

	k = 0;
	l = 0;
	new = NULL;
	k = ft_search(splt, '+');
	l = ft_search(str, '=');
	if (k == 1)
		new = ft_join_export(shell, str);
	else if (l == 1)
		new = ft_up_export(shell, str);
	else
	{
		free (new);
		return (shell->export);
	}
	ft_free(shell->export);
	return (new);
}

char	**ft_add_export_help2(char **env, char *str)
{
	int		b;
	int		i;
	char	**s_s;
	char	**new;

	i = 0;
	b = 0;
	new = malloc(sizeof(char *) * (ft_count(env) + 2));
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	s_s = ft_split(str, '=');
	b = ft_search(s_s[0], '+');
	if (b == 1)
		new[i] = ft_add(str);
	else
		new[i] = ft_strdup(str);
	new[++i] = NULL;
	ft_free(s_s);
	return (new);
}
