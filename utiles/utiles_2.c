/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:29:38 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/07 11:04:17 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	**ft_pwd(char **new)
{
	int		i;	
	char	**newenv;
	char	*pwd;

	i = 0;
	newenv = malloc(sizeof(char *) * (ft_count(new) + 1));
	if (!newenv)
		return (NULL);
	pwd = getcwd(NULL, 0);
	while (new[i])
	{
		if (strncmp(new[i], "PWD=", 4) != 0)
			newenv[i] = ft_strdup(new[i]);
		else
			newenv[i] = ft_strjoin("PWD=", pwd);
		i++;
	}
	newenv[i] = NULL;
	free(pwd);
	ft_free(new);
	return (newenv);
}

char	**ft_oldpwd(char **new)
{
	int		i;
	char	**newenv;

	i = 0;
	newenv = malloc(sizeof(char *) * (ft_count(new) + 1));
	if (!newenv)
		return (NULL);
	while (new[i])
	{
		if (strncmp(new[i], "OLDPWD=", 7) != 0)
			newenv[i] = ft_strdup(new[i]);
		else
			newenv[i] = ft_strjoin("OLD", ft_find_in_env(new, "PWD="));
		i++;
	}
	newenv[i] = NULL;
	ft_free(new);
	return (newenv);
}
