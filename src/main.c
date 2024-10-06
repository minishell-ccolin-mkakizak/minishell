/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/06 12:22:23 by ccolin           ###   ########.fr       */
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

int	main(void)
{
	char	*prompt;
	char	*hostname;
	int		exit;

	hostname = get_hostname();
	chdir(getenv("HOME"));
	while (1)
	{
		prompt = build_prompt(hostname);
		exit = minishell(clear_command(readline(prompt)));
		free(prompt);
		if (exit)
			break ;
	}
	clear_history();
	free(hostname);
	ft_printf("Exiting...\n");
}
