/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:09:16 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/26 14:40:42 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void exe_cd_home(t_cmnd_tbl *table)
{
	char *home_dir = get_env_var(table->envp, "HOME");
	if (home_dir == NULL)
	{
		ft_printf("minishell: HOME not set\n");
		return;
	}
	chdir(home_dir);
}

void exe_cd_tilde(char *path)
{
	char *home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return;
	}
	char *new_dir = ft_strjoin(home_dir, path + 1);
	if (new_dir == NULL)
	{
		ft_printf("minishell: Failed to allocate memory\n");
		return;
	}
	if(chdir(new_dir) != 0)
	{
		ft_printf("minishell: cd: %s: %s\n", new_dir, strerror(errno));
	}
	free(new_dir);
}

void exe_cd_bare(char *path)
{
	if(chdir(path) != 0)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
	}
}

void exe_cd(t_command *cmd, t_cmnd_tbl *table)
{
	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		exe_cd_home(table);
		return;
	}
	else
	{
		char *path = cmd->args[0];

		if (path[0] == '~')
		{
			exe_cd_tilde(path);
		}
		else
		{
			exe_cd_bare(path);
		}
	}
}
