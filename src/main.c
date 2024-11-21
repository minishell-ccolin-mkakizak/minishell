/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/20 23:24:05 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char*	get_input(void)
{
	char		*prompt;
	char		*hostname;
	char		*input;

	hostname = get_hostname();
	prompt = build_prompt(hostname);
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

	(void)argc;
	(void)argv;
	chdir(getenv("HOME"));
	init_command_table(&command_table, envp);
	while (1)
	{
		input = get_input();
			if (input)
				if (parse(input, command_table) == PARSING_ERROR)
					continue ;
		if (input)
			pipeline(command_table, envp);
		if (!input)
			break ;
	}
	free_env_list(command_table->envp);
	return (rl_clear_history(), ft_printf("Exiting...\n"), 0);
}
