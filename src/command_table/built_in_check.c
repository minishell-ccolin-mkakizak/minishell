/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/17 13:35:20 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_specific_builtin(t_command *command, const char *builtin)
{
	if ((ft_strlen(command->args[0]) == ft_strlen(builtin))
		&& strncmp(command->args[0], builtin, ft_strlen(builtin)) == 0)
		return (1);
	return (0);
}

int	is_built_in(t_command *command)
{
	if (is_specific_builtin(command, "echo"))
		return (1);
	if (is_specific_builtin(command, "cd"))
		return (1);
	if (is_specific_builtin(command, "pwd"))
		return (1);
	if (is_specific_builtin(command, "export"))
		return (1);
	if (is_specific_builtin(command, "unset"))
		return (1);
	if (is_specific_builtin(command, "env"))
		return (1);
	if (is_specific_builtin(command, "exit"))
		return (1);
	return (0);
}