/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:09:06 by minoka            #+#    #+#             */
/*   Updated: 2024/11/12 14:48:49 by mkakizak         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <minishell.h>

void exe_cd(t_command *cmd, t_env_list *env)
{
	puts(" you made it to cd!!");
}

void exe_pwd(t_command *cmd, t_env_list *env)
{
	char *dir;

	dir = getcwd(NULL, 0);
	printf("%s\n", dir);
}

void exe_env(t_command *cmd, t_env_list *env)
{
	// need to add some error checking also formattig is not quit right
	print_env_list(env);
}

int built_in_cmds(t_command *cmd, t_env_list *env)
{
	// char *command;
	// ft_printf("cmd is: %s\n", cmd->args[0]);
	// print_env_list(env);
	// if(cmd->args[0] == "echo")
	// {

	// }
	if(strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) == 0)
	{
		exe_cd(cmd, env);
	}
	if(strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) == 0)
	{
		exe_pwd(cmd, env);
	}
	// if(cmd->args[0] == "export")
	// {

	// }
	// if(cmd->args[0] == "unset")
	// {

	// }
	if(strncmp(cmd->args[0], "env", ft_strlen(cmd->args[0])) == 0)
	{
		exe_env(cmd, env);
	}
	// if(cmd->args[0] == "exit")
	// {

	// }

	// puts("is built in\n");
	exit(EXIT_SUCCESS);
	// NEED TO USE exit to stop this process
}
