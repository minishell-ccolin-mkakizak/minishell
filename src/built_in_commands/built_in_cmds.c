/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:09:06 by minoka            #+#    #+#             */
/*   Updated: 2024/12/10 13:25:35 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int built_in_cmds(t_command *cmd, t_cmnd_tbl *table, int is_child, t_fd *fd)
{
	if(is_match(cmd->command, "cd"))
	{
		exe_cd(cmd, table, fd);
	}
	if(is_match(cmd->command, "pwd"))
	{
		exe_pwd(cmd, table, fd);
	}
	if(is_match(cmd->command, "export"))
	{
		exe_export(cmd, table);
	}
	if(is_match(cmd->command, "unset"))
	{
		exe_unset(cmd, table);
	}
	if(is_match(cmd->command, "env"))
	{
		exe_env(cmd, table);
	}
	if(is_match(cmd->command, "exit"))
	{
		exe_exit(cmd, table);
	}
	if(is_child)
		exit(EXIT_SUCCESS);
	else
		return (0);
}
