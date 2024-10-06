/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:53 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/06 12:36:48 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_commands(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free_all(commands[i]);
		i++;
	}
	free(commands);
}

int	minishell(char *command)
{
	char	***commands;
	int		exit;

	exit = 0;
	if (!command)
		return (1);
	if (command[0] == '\0')
	{
		free(command);
		return (0);
	}
	add_history(command);
	commands = split_commands(command);
	exit = process_commands(commands);
	free_commands(commands);
	free(command);
	if (exit)
		return (1);
	return (0);
}
