/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/20 16:32:27 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		mode;

	(void)argc;
	(void)argv;

	char		*prompt;
	char		*hostname;
	char		*input;
	t_cmnd_tbl	*command_table;

	hostname = get_hostname();
	chdir(getenv("HOME"));
	init_command_table(&command_table, envp);

	while (1)
	{
		prompt = build_prompt(hostname);
		input = readline(prompt);
		if (!input)
		{
			free(prompt);
			break ;
		}
		free(prompt);
		parse(input, command_table);
		pipeline(command_table, envp);
	}
	free_env_list(command_table->envp);
	return (rl_clear_history(), free(hostname), ft_printf("Exiting...\n"), 0);
}
