/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:35:12 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/16 17:37:23 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_lexer(t_token **token, t_lx_dt *lx_dt, char *input)
{
	lx_dt->current_token = COMMAND;
	*token = malloc(sizeof(t_token));
	if (!*token)
		return ;
	(*token)->next = NULL;
	(*token)->token = NULL;
	(*token)->type = 0;
}

void	tokenize(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	i = skip_spaces_tabs(input, i);
	if (!input[i])
		return ;
	lx_dt->next_token_type = next_token_type(input, i);
	if (lx_dt->next_token_type == SINGLE_QUOTE)
	{
		single_quote_token(token, input, lx_dt, i);
		return ;
	}
	if (lx_dt->next_token_type == DOUBLE_QUOTE)
	{
		double_quote_token(token, input, lx_dt, i);
		return ;
	}
	if (lx_dt->next_token_type == HEREDOC || lx_dt->next_token_type == APPEND)
	{
		dbl_char_opr_tok(token, input, lx_dt, i);
		return ;
	}
	if (lx_dt->next_token_type == ENVP)
	{
		envp_token(token, input, lx_dt, i);
		return ;
	}
	if (lx_dt->next_token_type == INPUT_TYPE
		|| lx_dt->next_token_type == OUTPUT_TYPE
		|| lx_dt->next_token_type == PIPE)
	{
		sngl_char_opr_tok(token, input, lx_dt, i);
		return ;
	}
	if (lx_dt->next_token_type == STRING_TYPE)
		string_token(token, input, lx_dt, i);
	return ;
}

void	next_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	// syntax_check(token, lx_dt);
	i = skip_spaces_tabs(input, i);
	if (!input[i])
	{
		token->next = NULL;
		return ;
	}
	token->next = malloc(sizeof(t_token));
	if (!token->next)
		return ;
	token->next->token = NULL;
	token->next->type = 0;
	token->next->next = NULL;
	tokenize(token->next, input, lx_dt, i);
}

int	next_token_type(char *input, int i)
{
	if (input[i] == '>' && input[i + 1] == '>')
		return (APPEND);
	if (input[i] == '<' && input[i + 1] == '<')
		return (HEREDOC);
	if (input[i] == '\'')
		return (SINGLE_QUOTE);
	if (input[i] == '\"')
		return (DOUBLE_QUOTE);
	if (input[i] == '|')
		return (PIPE);
	if (input[i] == '<')
		return (INPUT_TYPE);
	if (input[i] == '>')
		return (OUTPUT_TYPE);
	if (input[i] == '$' && is_valid_key_char(input[i + 1], TRUE))
		return (ENVP);
	return (STRING_TYPE);
}