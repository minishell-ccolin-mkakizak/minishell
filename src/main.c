/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/18 13:47:08 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_envp(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	main(int argc, char **argv, char **envp)
{
	int		mode;
	char	**envp_copy;

	(void)argc;
	(void)argv;
	envp_copy = copy_envp(envp);
	mode = 2;

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
