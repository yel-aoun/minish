/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:51:37 by yel-aoun          #+#    #+#             */
/*   Updated: 2022/10/16 17:38:59 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_err_cmd(char *str, int k)
{
	write (2, "bash: ", 6);
	write(2, str, ft_strlen(str));
	write (2, ": ", 2);
	if (k == 1)
	{
		write (2, "command not found\n", \
			ft_strlen("command not found\n"));
		exit(127);
	}
	else if (k == 2)
	{
		write (2, "No such file or directory\n", \
			ft_strlen("No such file or directory\n"));
		exit (127);
	}
}

void	ft_error(char *str)
{
	perror (str);
	exit (0);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*result;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	ft_memmove(result, s1, len1);
	ft_memmove(&result[len1], s2, len2);
	result[len1 + len2] = '\0';
	free(s1);
	return (result);
}

void	ft_help_get_cmd(t_shell *shell, char **cmd)
{
	int	check;

	check = 0;
	check = command_with_path(shell, cmd);
	if (check == -1)
	{
		ft_free(shell->path);
		ft_err_cmd(cmd[0], 2);
	}
	if (check == 1)
	{
		shell->path = ft_get_path(shell->env);
		if (shell->path)
		{
			check = command_without_path(shell, cmd);
			if (check == -1)
			{
				ft_free(shell->path);
				ft_err_cmd(cmd[0], 1);
			}
			ft_free(shell->path);
		}
		else
			ft_err_cmd(cmd[0], 2);
	}
}

void	ft_simpl_help_in_exec(t_shell *shell, t_cmd *cmd, int k)
{
	ft_open_files(shell, cmd);
	if (shell->exit_creat == 0)
		first_c(cmd, shell, k);
	else
		exit (1);
}
