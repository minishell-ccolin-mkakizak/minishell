/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:35:12 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/30 12:55:32 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_tokens(t_token *token)
{
	if (token->next)
		free_tokens(token->next);
	free(token->token);
	free(token);
}

void	free_parser_data(t_token *token, t_lx_dt *lx_dt)
{
	free_tokens(token);
	free(lx_dt);
}
