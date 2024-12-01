/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:26:27 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/30 13:28:13 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init_lexer(t_token **token, t_lx_dt *lx_dt, t_cmnd_tbl *c)
{
	lx_dt->expecting_command = TRUE;
	lx_dt->previous_token_type = 0;
	lx_dt->next_token_type = 0;
	lx_dt->envp = c->envp;
	lx_dt->last_exit_status = c->last_exit_status;
	*token = malloc(sizeof(t_token));
	if (!*token)
		return (alloc_failed());
	(*token)->next = NULL;
	(*token)->token = NULL;
	(*token)->type = COMMAND;
	return (0);
}

void	init_new_token(t_token *token)
{
	token->next->token = NULL;
	token->next->type = 0;
	token->next->next = NULL;
}
