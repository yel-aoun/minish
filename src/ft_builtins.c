/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:53:54 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/29 17:03:07 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*ft_lower(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}

int	ft_check_builtins(t_shell *shell, t_cmd *command, int p)
{
	char	*cmp;
	t_cmd 	*cmd;
	int		k;                                                     /// i should add a struct to navigate in cmd without modifing in the real one

	k = 0;
	cmd = command;
	cmp = ft_strdup(cmd->cmd[0]);
	cmp = ft_lower(cmp);
	if (ft_strcmp(cmp, "echo") == 0)
		k = ft_echo(cmd);
	else if (ft_strcmp(cmp, "env") == 0)
		k = ft_put_env(shell, cmd);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		k = ft_cd(shell, cmd);
	else if (ft_strcmp(cmp, "pwd") == 0)
		k = ft_put_pwd();
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		k = ft_put_export(shell, cmd->cmd[1]);
	else if (ft_strcmp (cmd->cmd[0], "unset") == 0)
		k = ft_unset(shell, cmd);
	else if (ft_strcmp (cmd->cmd[0], "exit") == 0)
	{
		k = 1;
		ft_exit(cmd, p);
	}
	// else
	// 	printf("bash: %s: command not found\n", cmd->cmd[0]);
	free (cmp);
	return (k);
}
