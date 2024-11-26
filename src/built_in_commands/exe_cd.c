/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:09:16 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/26 17:04:41 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void exe_cd_home(t_cmnd_tbl *table)
{
	char *home_dir = get_env_var(table->envp, "HOME");
	if (home_dir == NULL)
	{
		ft_printf("minishell: HOME not set\n");
		table->last_exit_status = 1;
		return;
	}
	if(chdir(home_dir) != 0)
	{
		ft_printf("minishell: cd: %s: %s\n", home_dir, strerror(errno));
		table->last_exit_status = 1;
	}
	table->last_exit_status = 0;
	return ;
}

void exe_cd_tilde(char *path, t_cmnd_tbl *table)
{
	char *home_dir;
	char *new_dir;
	
	home_dir = getenv("HOME");
	if (home_dir == NULL)
	{
		ft_printf("minishell: cd: HOME not set\n");
		table->last_exit_status = 1;
		return; 
	}
	else 
	{
		table->last_exit_status = 0;
	}
	new_dir = ft_strjoin(home_dir, path + 1);
	if (new_dir == NULL)
	{
		ft_printf("minishell: cd: Cannot allocate memory\n");
		table->last_exit_status = 1;
		return;
	}
	if(chdir(new_dir) != 0)
	{
		ft_printf("minishell: cd: %s: %s\n", new_dir, strerror(errno));
		table->last_exit_status = 1;
	}
	else
	{
		table->last_exit_status = 0;
	} 

	free(new_dir);
	return ;
}

void exe_cd_bare(char *path, t_cmnd_tbl *table)
{
	if(chdir(path) != 0)
	{
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
		table->last_exit_status = 1;
	}
	else
	{
		table->last_exit_status = 0;
	}
	return ;
}

void exe_cd(t_command *cmd, t_cmnd_tbl *table)
{
	char *path;
	
	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		exe_cd_home(table);
		return;
	}
	if(cmd->args[1] != NULL)
	{
		ft_printf("minishell: cd: too many arguments\n");
		table->last_exit_status = 1;
		return;
	}
	else 
	{
		path = cmd->args[0];

		if (path[0] == '~')
		{
			exe_cd_tilde(path, table);
		}
		else
		{
			exe_cd_bare(path, table);
		}
	}


	//TODO: implement cd pwd overright on dir change
	//could possible add the - opstion using the OLDPWD env variable
	char *dir;

	dir = getcwd(NULL, 0);
	if(dir == NULL)
	{
		ft_printf("minishell: cd: %s\n", strerror(errno));
		table->last_exit_status = 1;
		return ;
	}

}
