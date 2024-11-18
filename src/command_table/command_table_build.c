/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_build.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/18 12:38:49 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	build_command_table(t_token *token, t_cmnd_tbl *command_table)
{
	t_command	*command;

	command_table->head = init_new_command(0);
	if (!command_table->head)
		return ;
	command = command_table->head;
	while (1)
	{
		token = add_args(token, command);
		token = add_operator(token, command);
		command->is_built_in = is_built_in(command);
		if (token && token->type == PIPE)
		{
			command->pipe_out = 1;
			command->next = init_new_command(1);
			command = command->next;
			token = token->next;
			continue ;
		}
		return ;
	}
}

t_token	*add_operator(t_token *token, t_command *command)
{
	while (token && token->type != PIPE)
	{
		if (token)
			token = handle_input_operator(token, command);
		if (token)
			token = handle_output_append_operator(token, command);
		if (token)
			token = handle_heredoc_operator(token, command);
	}
	return (token);
}

t_token	*add_args(t_token *token, t_command *command)
{
	t_token	*head;
	int		i;

	i = 0;
	head = token;
	while (token && (token->type == STRING_TYPE || token->type == DOUBLE_QUOTE
			|| token->type == SINGLE_QUOTE))
	{
		i++;
		token = token->next;
	}
	token = head;
	command->args = malloc(sizeof(char *) * (i + 1));
	if (!command->args)
		return (NULL);
	i = 0;
	while (token && (token->type == STRING_TYPE || token->type == DOUBLE_QUOTE
			|| token->type == SINGLE_QUOTE))
	{
		command->args[i] = ft_strdup(token->token);
		i++;
		token = token->next;
	}
	command->args[i] = NULL;
	return (token);
}