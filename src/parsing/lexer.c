/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:35:12 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/11 17:54:12 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*=============================================================================
Returns TRUE if there is no command in the tokens yet, if the current token
is a type of string, and if the previous command is not any operator except
for a pipe.
=============================================================================*/
int	is_command_token(t_lx_dt *lx_dt)
{
	return (lx_dt->expecting_command
		&& !is_previous_tok_operator_except_pipe(lx_dt)
		&& (lx_dt->next_token_type == SINGLE_QUOTE
			|| lx_dt->next_token_type == DOUBLE_QUOTE
			|| lx_dt->next_token_type == STRING_TYPE
			|| lx_dt->next_token_type == ENVP));
}

/*=============================================================================
Skips tabs and spaces, identifies the next token type, and calls the
appropriate function chain to create the token and call tokenize again for the
next one. Return value is used to pass any error occuring up the chain.
=============================================================================*/
int	tokenize(t_token *token, char **input, t_lx_dt *lx_dt, int i)
{
	if ((*input)[i])
		i = skip_spaces_tabs(input, i);
	if (!(*input)[i])
		return (0);
	lx_dt->next_token_type = next_token_type(input, i);
	if (is_command_token(lx_dt))
		return (command_token(token, input, lx_dt, i));
	if (lx_dt->next_token_type == SINGLE_QUOTE
		|| lx_dt->next_token_type == DOUBLE_QUOTE)
		return (quote_token(token, input, lx_dt, i));
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

int	is_last_token(char **input, int *i)
{
	int	is_last;

	is_last = FALSE;
	if ((*i < (int)ft_strlen(*input)))
		*i = skip_spaces_tabs(input, *i);
	if ((*i >= (int)ft_strlen(*input)))
		is_last = TRUE;
	return (is_last);
}

/*=============================================================================
Called after creation of a token. Skips tabs and spaces to determine if the
current token is the last one and passes the information to the syntax check
function. Initializes the next node and calls tokenize, or, if it's the last
token, ends the tokenization process.
=============================================================================*/
int	next_token(t_token *token, char **input, t_lx_dt *lx_dt, int i)
{
	int	is_last;

	is_last = is_last_token(input, &i);
	if (syntax_check(token, lx_dt, is_last))
		return (PARSING_ERROR);
	if (token->type == PIPE)
	{
		is_last = FALSE;
		lx_dt->expecting_command = TRUE;
		input = is_input_after_pipe(input, i);
		if (!input)
			return (PARSING_ERROR);
	}
	if (is_last)
	{
		token->next = NULL;
		return (0);
	}
	lx_dt->previous_token_type = token->type;
	token->next = malloc(sizeof(t_token));
	if (!token->next)
		return (alloc_failed());
	init_new_token(token);
	return (tokenize(token->next, input, lx_dt, i));
}

int	next_token_type(char **input, int i)
{
	if ((*input)[i] == '>' && (*input)[i + 1] == '>')
		return (APPEND);
	if ((*input)[i] == '<' && (*input)[i + 1] == '<')
		return (HEREDOC);
	if ((*input)[i] == '\'')
		return (SINGLE_QUOTE);
	if ((*input)[i] == '\"')
		return (DOUBLE_QUOTE);
	if ((*input)[i] == '|')
		return (PIPE);
	if ((*input)[i] == '<')
		return (INPUT_TYPE);
	if ((*input)[i] == '>')
		return (OUTPUT_TYPE);
	if ((*input)[i] == '$' && (is_valid_key_char((*input)[i + 1], TRUE)
			|| (*input)[i + 1] == '?'))
		return (ENVP);
	return (STRING_TYPE);
}
