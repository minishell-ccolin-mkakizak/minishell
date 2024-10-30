/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:09:06 by minoka            #+#    #+#             */
/*   Updated: 2024/10/30 19:07:02 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void exe_cd(t_command *cmd, char *envp[])
{
	puts(" you made it to cd!!");


}

void exe_pwd(t_command *cmd, char *envp[])
{
	char *dir;

	dir = getcwd(NULL, 0);
	ft_printf("%s\n", dir);

}

int built_in_cmds(t_command *cmd, char *envp[])
{
	// char *command;
	ft_printf("cmd is: %s\n", cmd->args[0]);
	// if(cmd->args[0] == "echo")
	// {

	// }
	if(strncmp(cmd->args[0], "cd", ft_strlen(cmd->args[0])) == 0)
	{
		exe_cd(cmd, envp);
	}
	if(strncmp(cmd->args[0], "pwd", ft_strlen(cmd->args[0])) == 0)
	{
		exe_pwd(cmd, envp);
	}
	// if(cmd->args[0] == "export")
	// {

	// }
	// if(cmd->args[0] == "unset")
	// {

	// }
	// if(cmd->args[0] == "env")
	// {

	// }
	// if(cmd->args[0] == "exit")
	// {

	// }

	// puts("is built in\n");
	exit(EXIT_SUCCESS);
	// NEED TO USE exit to stop this process
}
