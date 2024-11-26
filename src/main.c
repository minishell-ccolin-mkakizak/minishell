/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/26 14:50:26 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		// free(prompt);
		// free(hostname);
		return (input); 
	}
	return (NULL);
}

volatile sig_atomic_t sig_received = 0;

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

		init_signals();
		if (sig_received)
		{
			// sig_received = 0;
			continue;
		}

		// printf("sig_received = %d\n", sig_received);
		input = get_input();
		if (input)
		{
			parser_return_value = parse(input, command_table);
			if (parser_return_value == PARSING_ERROR)
				continue ;
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
