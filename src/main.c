/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/15 12:26:52 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Replaces tabs with spaces and removes extra spaces, ensuring only
single spaces remain */
char	*clear_command(char *command)
{
	int		i;
	int		j;
	char	*cleaned;

	if (!command)
		return (NULL);
	if (command[0] == '\0')
		return (command);
	i = 0;
	j = 0;
	cleaned = (char *)malloc(sizeof(char) * (ft_strlen(command) + 1));
	if (!cleaned)
		return (NULL);
	while (command[i])
	{
		if (command[i] == '\t')
			command[i] = ' ';
		if (command[i] != ' ' || (j > 0 && cleaned[j - 1] != ' '))
			cleaned[j++] = command[i];
		i++;
	}
	cleaned[j] = '\0';
	free(command);
	return (cleaned);
}

char	**init_envp(void)
{
	char	**envp;

	envp = malloc(sizeof(char *) * 1);
	if (!envp)
		return (NULL);
	envp[0] = NULL;
	return (envp);
}

t_command	init_head(void)
{
	t_command	head;

	head = malloc(sizeof(t_command) * 1);
	if (!head)
		return (NULL);
	return (head);
}

t_command_table	init_table(void)
{
	t_command_table	table;

	table = malloc(1, sizeof(t_command_table));
	if (!table)
		return (NULL);
	table.head = init_head();
	table.exit_status = 0;
	table.envp = init_envp();
	return (table);
}

int	main(void)
{
	char			*prompt;
	char			**envp;
	char			*hostname;
	int				exit;
	t_command_table	table;

	table = init_table();
	hostname = get_hostname();
	chdir(getenv("HOME"));
	while (1)
	{
		prompt = build_prompt(hostname);
<<<<<<< Updated upstream
		exit = minishell(parsing(readline(prompt), table));
=======
		exit = minishell(clear_command(readline(prompt)));
		
>>>>>>> Stashed changes
		free(prompt);
		if (exit)
			break ;
	}
	clear_history();
	free(hostname);
	ft_printf("Exiting...\n");
}
