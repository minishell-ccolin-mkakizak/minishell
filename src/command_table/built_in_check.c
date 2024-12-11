/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/11 14:32:03 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_specific_builtin(t_command *command, const char *builtin)
{
	if ((ft_strlen(command->command) == ft_strlen(builtin))
		&& ft_strncmp(command->command, builtin, ft_strlen(builtin)) == 0)
		return (1);
	return (0);
}

int	is_built_in(t_command *command)
{
	if (!command->command)
		return (0);
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
