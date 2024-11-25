/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:57:55 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/24 12:45:43 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_previous_tok_operator_except_pipe(t_lx_dt *lx_dt)
{
	return (lx_dt->previous_token_type == INPUT_TYPE
		|| lx_dt->previous_token_type == OUTPUT_TYPE
		|| lx_dt->previous_token_type == HEREDOC
		|| lx_dt->previous_token_type == APPEND);
}

int	is_current_tok_operator_except_pipe(t_token *token)
{
	return (token->type == INPUT_TYPE || token->type == OUTPUT_TYPE
		|| token->type == HEREDOC || token->type == APPEND);
}

int	is_arg(int type)
{
	return (type == STRING_TYPE || type == SINGLE_QUOTE || type == DOUBLE_QUOTE
		|| type == ENVP);
}

/*=============================================================================
The current token is approved or not based on the previous token's type.
For instance if the previous token is an operator and the current one is not
an argument, it is not approved.
The fact that ft_printf returns the number of characters printed is used to
make is_error TRUE if an error message is printed.
=============================================================================*/
int	syntax_check(t_token *token, t_lx_dt *lx_dt, int is_last)
{
	int		is_error;
	char	*s;

	s = "minishell: syntax error near unexpected token";
	is_error = FALSE;
	if (is_last && is_current_tok_operator_except_pipe(token))
		is_error = ft_printf("%s `newline'\n");
	if ((lx_dt->previous_token_type == 0 || lx_dt->previous_token_type == PIPE)
		&& token->type == PIPE)
		is_error = ft_printf("%s `%s'\n", token->token);
	if (is_previous_tok_operator_except_pipe(lx_dt) && !is_arg(token->type))
		is_error = ft_printf("%s `%s'\n", token->token);
	if (is_previous_tok_operator_except_pipe(lx_dt) && !lx_dt->expecting_command
		&& !is_arg(token->type))
		is_error = ft_printf("%s `%s'\n", token->token);
	return (is_error);
}
