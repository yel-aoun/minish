/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:44:46 by araysse           #+#    #+#             */
/*   Updated: 2022/10/12 15:32:40 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

t_token	*init_tok(int type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(struct token_struct));
	token->e_type = type;
	token->value = value;
	return (token);
}
