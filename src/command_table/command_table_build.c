/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_build.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/26 14:04:17 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	process_tokens(t_token **token, t_command *command)
{
	while (*token && (*token)->type != PIPE)
	{
		if (*token)
			*token = add_command(*token, command);
		if (*token)
			if (add_args(token, command, 0))
				return (ALLOCATION_FAIL);
		if (*token)
			if (add_operator(token, command))
				return (ALLOCATION_FAIL);
	}
	command->is_built_in = is_built_in(command);
	return (0);
}

int	build_command_table(t_token *token, t_cmnd_tbl *command_table)
{
	t_command	*command;

	if (init_new_command(&command_table->head, 0))
		return (ALLOCATION_FAIL);
	command = command_table->head;
	while (1)
	{
		if (process_tokens(&token, command))
			return (ALLOCATION_FAIL);
		if (token && token->type == PIPE)
		{
			command->pipe_out = 1;
			if (init_new_command(&command->next, 1))
				return (ALLOCATION_FAIL);
			command = command->next;
			token = token->next;
			continue ;
		}
		return (0);
	}
}

t_token	*add_command(t_token *token, t_command *command)
{
	if (token->type == COMMAND)
	{
		if (!command)
			command->command = NULL;
		command->command = ft_strdup(token->token);
		return (token->next);
	}
	return (token);
}

int	add_operator(t_token **token, t_command *command)
{
	if (*token)
	{
		*token = handle_input_operator(*token, command);
		if (!token)
			return (alloc_failed());
	}
	if (*token)
		if (handle_output_append_operator(token, command))
			return (ALLOCATION_FAIL);
	if (*token)
		*token = handle_heredoc_operator(*token, command);
	return (0);
}

int	add_args(t_token **token, t_command *command, int i)
{
	t_token	*head;

	if (!is_arg((*token)->type))
		return (0);
	head = *token;
	while (*token && (is_arg((*token)->type)))
	{
		i++;
		*token = (*token)->next;
	}
	*token = head;
	command->args = malloc(sizeof(char *) * (i + 1));
	if (!command->args)
		return (alloc_failed());
	i = 0;
	while (*token && (is_arg((*token)->type)))
	{
		command->args[i] = ft_strdup((*token)->token);
		i++;
		*token = (*token)->next;
	}
	command->args[i] = NULL;
	return (0);
}
