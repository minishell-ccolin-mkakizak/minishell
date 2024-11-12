/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:09:06 by minoka            #+#    #+#             */
/*   Updated: 2024/11/12 15:40:12 by mkakizak         ###   ########.fr       */
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
	ft_printf("%s\n", dir);
}

void exe_env(t_command *cmd, t_env_list *env)
{
	// need to add some error checking also formattig is not quit right
	print_env_list(env);
}

void exe_unset(t_command *cmd, t_env_list *env)
{
	int i;

	i = 0;
}

int is_match(char *str1, char *str2)
{
	if(strncmp(str1, str2, ft_strlen(str1)) == 0)
		return (TRUE);
	else
		return (FALSE);
}

int built_in_cmds(t_command *cmd, t_env_list *env)
{
	// char *command;
	// ft_printf("cmd is: %s\n", cmd->args[0]);
	// print_env_list(env);
	// if(cmd->args[0] == "echo")
	// {

	// }
	if(is_match(cmd->args[0], "cd"))
	{
		// exe_cd(cmd, env);
	}
	if(is_match(cmd->args[0], "pwd"))
	{
		exe_pwd(cmd, env);
	}
	// if(cmd->args[0] == "export")
	// {

	// }
	if(is_match(cmd->args[0], "unset"))
	{
		exe_unset(cmd, env);
	}
	if(is_match(cmd->args[0], "env"))
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
