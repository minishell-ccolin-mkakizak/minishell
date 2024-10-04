/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:53 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/04 09:55:19 by ccolin           ###   ########.fr       */
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
	char ***commands;
	int	exit;

	exit = 0;
	commands = split_commands(command);
	free(command);
	exit = process_commands(commands);
	free_commands(commands);
	if (exit)
		return (1);
	return (0);
}
