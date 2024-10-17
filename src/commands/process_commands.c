/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 21:39:52 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/14 15:04:36 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_command(char **command)
{
	if (ft_strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		return (1);
	if (ft_strncmp(command[0], "cd", ft_strlen(command[0])) == 0)
		cd(command);
	if (ft_strncmp(command[0], "pwd", ft_strlen(command[0])) == 0)
		pwd(command);
	else
	{
		// this cant be implemented quite yet
		// execute_cmd(command);
	}
	return (0);
}

int	process_commands(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		if (run_command(commands[i]))
			return (1);
		i++;
	}
	return (0);
}
