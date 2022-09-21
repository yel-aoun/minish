/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 11:53:54 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/09/20 14:26:21 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*ft_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}

void	ft_check_builtins(t_shell *shell, t_cmd *cmd)
{
	char	*cmp;

	cmp = ft_strdup(cmd->cmd[0]);
	cmp = ft_lower(cmp);
	if (ft_strcmp(cmp, "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(cmp, "env") == 0)
		ft_put_env(shell);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		ft_cd(shell);
	else if (ft_strcmp(cmp, "pwd") == 0)
		ft_put_pwd();
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		ft_put_export(shell, cmd->cmd[1]);
	else if (ft_strcmp (cmd->cmd[0], "unset") == 0)
		ft_unset(shell, cmd->cmd[1]);
	else if (ft_strcmp (cmd->cmd[0], "exit") == 0)
		ft_exit(shell);
	// else
	// 	printf("bash: %s: command not found\n", cmd->cmd[0]);
	free (cmp);
}
