/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:35:31 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/18 15:04:02 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(char *input, t_cmnd_tbl *command_table)
{
	t_token	*token;
	t_lx_dt	*lx_dt;

	lx_dt = malloc(sizeof(t_lx_dt));
	if (!lx_dt)
		return ;
	token = malloc(sizeof(t_token));
	if (!token)
		return ;
	init_lexer(&token, lx_dt, input);
	tokenize(token, input, lx_dt, 0);
	// expend_envps(token);
	print_tokens(token);
	add_history(input);
	free(input);
	build_command_table(token, command_table);
	print_cmnd_tbl(command_table);
	free_parser_data(token, lx_dt);
	return ;
}

int	main_parsing(char **envp)
{
	char		*prompt;
	char		*hostname;
	char		*input;
	t_cmnd_tbl	*command_table;

	hostname = get_hostname();
	chdir(getenv("HOME"));

	command_table->envp = init_env(envp);
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
	return (clear_history(), free(hostname), ft_printf("Exiting...\n"), 0);
}

// free and exit if failed malloc
// substr malloc failsafe
// make re
