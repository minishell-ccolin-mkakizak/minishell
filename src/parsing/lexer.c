/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:35:12 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/23 10:48:00 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_lexer(t_token **token, t_lx_dt *lx_dt, char *input, t_cmnd_tbl *c)
{
	lx_dt->expecting_command = TRUE;
	lx_dt->previous_token_type = 0;
	lx_dt->pre_previous_token_type = 0;
	lx_dt->next_token_type = 0;
	lx_dt->envp = c->envp;
	*token = malloc(sizeof(t_token));
	if (!*token)
		return ;
	(*token)->next = NULL;
	(*token)->token = NULL;
	(*token)->type = 0;
}

int	is_command_token(t_lx_dt *lx_dt)
{
	return (lx_dt->expecting_command && !is_previous_tok_operator_except_pipe(lx_dt) && (lx_dt->next_token_type == SINGLE_QUOTE || lx_dt->next_token_type == DOUBLE_QUOTE || lx_dt->next_token_type == STRING_TYPE || lx_dt->next_token_type == ENVP));
}

int	tokenize(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	i = skip_spaces_tabs(input, i);
	if (!input[i])
		return (0);
	lx_dt->next_token_type = next_token_type(input, i);
	if (is_command_token(lx_dt))
		return (command_token(token, input, lx_dt, i));
	if (lx_dt->next_token_type == SINGLE_QUOTE)
		return (single_quote_token(token, input, lx_dt, i));
	if (lx_dt->next_token_type == DOUBLE_QUOTE)
		return (double_quote_token(token, input, lx_dt, i));
	if (lx_dt->next_token_type == HEREDOC || lx_dt->next_token_type == APPEND)
		return (dbl_char_opr_tok(token, input, lx_dt, i));
	if (lx_dt->next_token_type == ENVP)
		return (envp_token(token, input, lx_dt, i));
	if (lx_dt->next_token_type == INPUT_TYPE
		|| lx_dt->next_token_type == OUTPUT_TYPE
		|| lx_dt->next_token_type == PIPE)
		return (sngl_char_opr_tok(token, input, lx_dt, i));
	if (lx_dt->next_token_type == STRING_TYPE)
		return (string_token(token, input, lx_dt, i));
	return (0);
}

int	is_previous_tok_operator_except_pipe(t_lx_dt *lx_dt)
{
	return (lx_dt->previous_token_type == INPUT_TYPE || lx_dt->previous_token_type == OUTPUT_TYPE || lx_dt->previous_token_type == HEREDOC || lx_dt->previous_token_type == APPEND);
}

int	is_current_tok_operator_except_pipe(t_token *token)
{
	return (token->type == INPUT_TYPE || token->type == OUTPUT_TYPE || token->type == HEREDOC || token->type == APPEND);
}

int	is_arg(int type)
{
	return (type == STRING_TYPE || type == SINGLE_QUOTE || type == DOUBLE_QUOTE || type == ENVP);
}

int	syntax_check(t_token *token, t_lx_dt *lx_dt, int is_last)
{
	int	is_error;
	is_error = FALSE;
	if (is_last && is_current_tok_operator_except_pipe(token))
		is_error = ft_printf("minishell: syntax error near unexpected token `newline'\n");
	if ((lx_dt->previous_token_type == 0 || lx_dt->previous_token_type == PIPE) && token->type == PIPE)
		is_error = ft_printf("minishell: syntax error near unexpected token `%s'\n", token->token);
	if (is_previous_tok_operator_except_pipe(lx_dt) && !is_arg(token->type))
		is_error = ft_printf("minishell: syntax error near unexpected token `%s'\n", token->token);
	if (is_previous_tok_operator_except_pipe(lx_dt) && !lx_dt->expecting_command && !is_arg(token->type))
		is_error = ft_printf("minishell: syntax error near unexpected token `%s'\n", token->token);
	return (is_error);
}

int	next_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int		is_last;
	
	is_last = FALSE;
	i = skip_spaces_tabs(input, i);
	if (!input[i])
		is_last = TRUE;
	if (syntax_check(token, lx_dt, is_last))
		return (PARSING_ERROR);
	if (is_last)
	{
		token->next = NULL;
		return (0);
	}
	lx_dt->previous_token_type = token->type;
	token->next = malloc(sizeof(t_token));
	if (!token->next)
		return (0);
	token->next->token = NULL;
	token->next->type = 0;
	token->next->next = NULL;
	return (tokenize(token->next, input, lx_dt, i));
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

// maloc checks include ft_substr and ft_strjoin and ft_substr
