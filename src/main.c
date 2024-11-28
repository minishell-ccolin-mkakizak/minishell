/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/28 16:08:28 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		if (whitespace_only_handler(input))
		{
			add_history(input);
			free(input);
			continue ;
		}
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
			parser_return_value = parse(&input, command_table);
			if (parser_return_value == PARSING_ERROR)
			{
				command_table->last_exit_status = 258;
				continue ;
			}
			if (parser_return_value == ALLOCATION_FAIL)
			{
				//INSERT FUNCTION THAT FREES THE COMMAND TABLE
				break ;
			}
			pipeline(command_table, envp);
		}
		if (!input)
			break ;
	}
	free_command_table(command_table);
	return (rl_clear_history(), ft_printf("Exiting...\n"), 0);
}
