/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/17 13:35:07 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*handle_input_operator(t_token *token, t_command *command)
{
	if (token->type == INPUT_TYPE)
	{
		token = token->next;
		command->input_file = ft_strdup(token->token);
		token = token->next;
	}
	return (token);
}

t_token	*handle_output_append_operator(t_token *token, t_command *command)
{
	if (token->type == OUTPUT_TYPE)
	{
		token = token->next;
		command->output_file = ft_strdup(token->token);
		token = token->next;
	}
	else if (token->type == APPEND)
	{
		token = token->next;
		command->append = ft_strdup(token->token);
		token = token->next;
	}
	return (token);
}

t_token	*handle_heredoc_operator(t_token *token, t_command *command)
{
	if (token->type == HEREDOC)
	{
		token = token->next;
		command->output_file = ft_strdup(token->token);
		token = token->next;
	}
	return (token);
}