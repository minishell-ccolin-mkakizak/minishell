/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/17 13:12:48 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_command_table(t_cmnd_tbl **command_table)
{
	ft_printf("init command table%c", 10); //debug
	*command_table = malloc(sizeof(t_cmnd_tbl));
	if (!*command_table)
		return ;
	(*command_table)->head = NULL;
	(*command_table)->exit_shell = 0;
	(*command_table)->exit_status = 0;
}

void	init_command(t_command *command, int is_pipe)
{
	ft_printf("init command%c", 10); //debug
	if (!command)
		return ;
	command->args = NULL;
	command->input_file = NULL;
	command->output_file = NULL;
	command->heredoc_delimiter = NULL;
	command->append = NULL;
	if (is_pipe)
		command->pipe_in = 1;
	else
		command->pipe_in = 0;
	command->pipe_out = 0;
	command->is_built_in = 0;
	command->next = NULL;
}

t_token	*add_args(t_token *token, t_command *command)
{
	ft_printf("add args%c", 10); //debug
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

t_token	*add_operator(t_token *token, t_command *command)
{
	ft_printf("add operator%c", 10); //debug
	while (token && token->type != PIPE)
	{
		token = handle_input_operator(token, command);
		token = handle_output_append_operator(token, command);
		ft_printf("append fuc exited%c", 10); //debug
		token = handle_heredoc_operator(token, command);
	}
	return (token);
}

t_command	*init_new_command(int is_pipe)
{
	t_command	*command;
	ft_printf("init new command%c", 10); //debug
	command = malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	init_command(command, is_pipe);
	return (command);
}

int	is_specific_builtin(t_command *command, const char *builtin)
{
	if ((ft_strlen(command->args[0]) == ft_strlen(builtin))
		&& strncmp(command->args[0], builtin, ft_strlen(builtin)) == 0)
		return (1);
	return (0);
}

int	is_built_in(t_command *command)
{
	ft_printf("is built in = %s%c", command->args[0], 10); //debug
	if (is_specific_builtin(command, "echo"))
		return (1);
	if (is_specific_builtin(command, "cd"))
		return (1);
	if (is_specific_builtin(command, "pwd"))
		return (1);
	if (is_specific_builtin(command, "export"))
		return (1);
	if (is_specific_builtin(command, "unset"))
		return (1);
	if (is_specific_builtin(command, "env"))
		return (1);
	if (is_specific_builtin(command, "exit"))
		return (1);
	return (0);
}

void	build_command_table(t_token *token, t_cmnd_tbl *command_table)
{
	t_command	*command;
	ft_printf("build command table\n"); //debug
	command_table->head = init_new_command(0);
	if (!command_table->head)
		return ;
	command = command_table->head;
	while (1)
	{
		token = add_args(token, command);
		token = add_operator(token, command);
		if (is_built_in(command))
			command->is_built_in = 1;
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
