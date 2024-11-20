/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:09:06 by minoka            #+#    #+#             */
/*   Updated: 2024/11/20 15:19:02 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int built_in_cmds(t_command *cmd, t_cmnd_tbl *table, int is_child)
{
	// char *command;
	// ft_printf("cmd is: %s\n", cmd->args[0]);
	// print_env_list(env);
	// echo is already on bin/echo do we really need to make one?
	// if(cmd->args[0] == "echo")
	// {

	// }
	if(is_match(cmd->args[0], "cd"))
	{
		exe_cd(cmd, table);
	}
	if(is_match(cmd->args[0], "pwd"))
	{
		exe_pwd(cmd, table);
	}
	if(is_match(cmd->args[0], "export"))
	{
		exe_export(cmd, table);
	}
	if(is_match(cmd->args[0], "unset"))
	{
		exe_unset(cmd, table);
		// print_env_list(env);
	}
	if(is_match(cmd->args[0], "env"))
	{
		exe_env(cmd, table);
	}
	if(is_match(cmd->args[0], "exit"))
	{
		exe_exit(cmd, table);
	}
	// puts("is built in\n");
	// ft_printf("[builtin]is_child is%d\n", is_child);
	if(is_child)
		exit(EXIT_SUCCESS);
	else
		return (0);
	// NEED TO USE exit to stop this process
}
