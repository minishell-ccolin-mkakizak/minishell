/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/11/18 16:22:32 by ccolin           ###   ########.fr       */
=======
/*   Updated: 2024/11/18 16:51:26 by mkakizak         ###   ########.fr       */
>>>>>>> main
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

	// command_table->envp = init_env(envp);
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
		init_command_table(&command_table);
		parse(input, command_table);
		pipeline(command_table, envp);
	}
	// free_env_list(command_table->envp);
<<<<<<< HEAD
	return (rl_clear_history(), free(hostname), ft_printf("Exiting...\n"), 0);
=======
	return (clear_history(), free(hostname), ft_printf("Exiting...\n"), 0);
>>>>>>> main
}
