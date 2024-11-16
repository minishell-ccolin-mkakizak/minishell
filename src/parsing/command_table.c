/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/16 17:41:08 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_command_table(t_cmnd_tbl **command_table)
{
	*command_table = malloc(sizeof(t_cmnd_tbl));
	if (!*command_table)
		return ;
	(*command_table)->head = NULL;
	(*command_table)->exit_shell = 0;
	(*command_table)->exit_status = 0;
}

void	init_command(t_command *command)
{
	if (!command)
		return ;
	command->args = NULL;
	command->input_file = NULL;
	command->output_file = NULL;
	command->heredoc_delimiter = NULL;
	command->append = 0;
	command->pipe_in = 0;
	command->pipe_out = 0;
	command->exec_cond = 0;
	command->is_built_in = 0;
	command->next = NULL;
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

t_token	*add_operator(t_token *token, t_command *command)
{
	// if (token->type = INPUT_TYPE)
	// {
	// 	token = token->next;
	// 	command->input_file = ft_strdup(token->token);
	// 	token = token->next;
	// }
	// if (token->type = OUTPUT_TYPE)
	// {
	// 	token = token->next;
	// 	command->input_file = ft_strdup(token->token);
	// }
	return (NULL);
}

void	build_command_table(t_token *token, t_cmnd_tbl *command_table)
{
	t_command *command;

	command_table->head = malloc(sizeof(t_command));
	if (!command_table->head)
		return ;
	command = command_table->head;
	init_command(command);
	while (1)
	{
		token = add_args(token, command);
		token = add_operator(token, command);
	}
}