/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tstrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:58:24 by araysse           #+#    #+#             */
/*   Updated: 2022/09/05 16:28:22 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

unsigned int	ft_tstrlen(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return(0);
	while (str[i])
		i++;
	return (i);
}