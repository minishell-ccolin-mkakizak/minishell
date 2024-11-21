/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/21 18:33:01 by mkakizak         ###   ########.fr       */
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

volatile sig_atomic_t sig_received = 0;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\nReceived SIGINT (Ctrl+C)\n"); fflush(stdout);
		sig_received = 1;
	}
	else if (sig == SIGQUIT)
	{
		ft_printf("\nReceived SIGQUIT (Ctrl+\\)\n");
	}
	else if (sig == SIGTERM)
	{
		ft_printf("\nReceived SIGTERM\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_cmnd_tbl	*command_table;

	(void)argc;
	(void)argv;
	chdir(getenv("HOME"));
	init_command_table(&command_table, envp);

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
	while (1)
	{

		if (sig_received)
		{
			sig_received = 0;
			continue;
		}

		printf("sig_received = %d\n", sig_received);
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
