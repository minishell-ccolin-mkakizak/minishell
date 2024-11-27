/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/27 15:09:35 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	whitespace_only_handler(char *input)
{
	int		i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (!input[i])
		return (1);
	return (0);
}

char	*get_input(void)
{
	char	*prompt;
	char	*hostname;
	char	*input;

	hostname = get_hostname();
	prompt = build_prompt(hostname);
	if (!prompt)
	{
		free(hostname);
		return (NULL);
	}
	while (1)
	{
		input = readline(prompt);
		if (!input)
			break ;
		if (input[0] == 0)
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (whitespace_only_handler(input))
		{
			free(input);
			continue ;
		}
		free(prompt);
		free(hostname);
		return (input);
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_cmnd_tbl	*command_table;
	int			parser_return_value;

	(void)argc;
	(void)argv;
	chdir(getenv("HOME"));
	if (init_command_table(&command_table, envp))
		return (ALLOCATION_FAIL);
	while (1)
	{
		input = get_input();
		if (input)
		{
			parser_return_value = parse(input, command_table);
			if (parser_return_value == PARSING_ERROR)
			{
				command_table->exit_status = 258;
				continue ;
			}
			if (parser_return_value == ALLOCATION_FAIL)
			{
				//INSERT FUNCTION THAT FREES THE COMMAND TABLE
				break ;
			}
		}
		if (input)
			pipeline(command_table, envp);
		if (!input)
			break ;
	}
	free_env_list(command_table->envp);
	return (rl_clear_history(), ft_printf("Exiting...\n"), 0);
}
