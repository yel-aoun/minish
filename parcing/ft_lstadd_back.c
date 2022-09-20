/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-aoun <yel-aoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:55:35 by araysse           #+#    #+#             */
/*   Updated: 2022/09/20 12:44:44 by yel-aoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_lstadd_back(t_cmd **alst, t_cmd *new)
{
	t_cmd	*tmp;

	tmp  = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_lstnew(t_cmd **cmd, t_redirection* redir, char* str)
{
	(*cmd) = malloc(sizeof(t_cmd));
	(*cmd)->cmd = ft_tsplit(str, 127);
	(*cmd)->redirection = redir;
}

void	ft_lstadd_bak(t_redirection **alst, t_redirection *new)
{
	t_redirection	*tmp;

	tmp  = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}