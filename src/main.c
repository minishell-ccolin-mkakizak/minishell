/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/13 12:29:58 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_global;

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

void	reset_global_status(int *exit_status)
{
	if (g_global)
	{	
		*exit_status = g_global;
		g_global = 0;
	}
}

int	minishell_loop(t_cmnd_tbl *command_table)
{
	char	*input;
	int		return_value;

	init_signals(0);
	input = get_input();
	if (input)
	{
		reset_global_status(&command_table->last_exit_status);
		return_value = parse(&input, command_table);
		if (return_value == PARSING_ERROR)
		{
			command_table->last_exit_status = 2;
			return (PARSING_ERROR);
		}
		if (return_value == ALLOCATION_FAIL)
			return (ALLOCATION_FAIL);
		pipeline(command_table);
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
		return_value = minishell_loop(command_table);
		if (return_value == PARSING_ERROR)
			continue ;
		if (return_value == ALLOCATION_FAIL || return_value == NO_INPUT)
			break ;
	}
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
