/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:09:06 by minoka            #+#    #+#             */
/*   Updated: 2024/11/14 13:49:15 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int built_in_cmds(t_command *cmd, t_env_list *env)
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
		exe_cd(cmd, env);
	}
	if(is_match(cmd->args[0], "pwd"))
	{
		exe_pwd(cmd, env);
	}
	if(is_match(cmd->args[0], "export"))
	{
		exe_export(cmd, env);
	}
	if(is_match(cmd->args[0], "unset"))
	{
		exe_unset(cmd, env);
		print_env_list(env);
	}
	if(is_match(cmd->args[0], "env"))
	{
		exe_env(cmd, env);
	}
	if(is_match(cmd->args[0], "exit"))
	{
		exe_exit(cmd, env);
	}

	// puts("is built in\n");
	exit(EXIT_SUCCESS);
	// NEED TO USE exit to stop this process
}