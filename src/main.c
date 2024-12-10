/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 15:19:38 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	whitespace_only_handler(char **input)
{
	int	i;

	i = 0;
	while ((*input)[i] && ((*input)[i] == ' ' || (*input)[i] == '\t'))
		i++;
	if (!(*input)[i])
	{
		add_history(*input);
		free(*input);
		return (1);
	}
	return (0);
}

char	*get_input(void)
{
	char	*prompt;
	char	*hostname;
	char	*input;

	while (1)
	{
		hostname = get_hostname();
		prompt = build_prompt(hostname);
		free(hostname);
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
		if (input[0] == 0)
		{
			free(input);
			continue ;
		}
		if (whitespace_only_handler(&input))
			continue ;
		return (input);
	}
	return (NULL);
}

int	minishell_loop(t_cmnd_tbl *command_table, char **envp)
{
	char	*input;
	int		return_value;

	if (init_signals())
		return (SIGNAL_RECEIVED);
	input = get_input();
	if (input)
	{
		ignore_signals();
		return_value = parse(&input, command_table);
		if (return_value == PARSING_ERROR)
		{
			command_table->last_exit_status = 258;
			return (PARSING_ERROR);
		}
		if (return_value == ALLOCATION_FAIL)
			return (ALLOCATION_FAIL);
		pipeline(command_table, envp);
		if (command_table->head)
			free_command_list(command_table);
	}
	if (!input)
		return (NO_INPUT);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int			return_value;
	t_cmnd_tbl	*command_table;

	(void)argc;
	(void)argv;
	if (init_command_table(&command_table, envp))
		return (ALLOCATION_FAIL);
	while (1)
	{
		return_value = minishell_loop(command_table, envp);
		if (return_value == PARSING_ERROR || return_value == SIGNAL_RECEIVED)
			continue ;
		if (return_value == ALLOCATION_FAIL || return_value == NO_INPUT)
			break ;
	}
	exit(EXIT_SUCCESS);
}
