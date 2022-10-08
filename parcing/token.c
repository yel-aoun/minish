/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araysse <araysse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:44:46 by araysse           #+#    #+#             */
/*   Updated: 2022/10/06 12:11:12 by araysse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

token_t	*init_tok(int type, char *value)
{
	token_t	*token;

	token = calloc(1, sizeof(struct token_struct));
	token->type = type;
	token->value = value;
	// system("leaks minishell");
	return (token);
}
