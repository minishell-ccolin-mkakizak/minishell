/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:09:16 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 15:33:39 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exe_cd_home(t_cmnd_tbl *table, t_fd *fd)
{
	char	*home_dir;

	home_dir = get_env_var(table->envp, "HOME");
	if (home_dir == NULL)
	{
		restore_fd(fd);
		ft_printf("minishell: HOME not set\n");
		table->last_exit_status = 1;
		return ;
	}
	if (chdir(home_dir) != 0)
	{
		restore_fd(fd);
		ft_printf("minishell: cd: %s: %s\n", home_dir, strerror(errno));
		table->last_exit_status = 1;
	}
	table->last_exit_status = 0;
	return (free(home_dir));
}

char	*build_new_dir(char *path)
{
	char	*home_dir;

	home_dir = getenv("HOME");
	if (!home_dir)
		return (NULL);
	return (ft_strjoin(home_dir, path + 1));
}

void	change_to_new_dir(char *new_dir, t_fd *fd, t_cmnd_tbl *table)
{
	if (chdir(new_dir) != 0)
	{
		restore_fd(fd);
		ft_printf("minishell: cd: %s: %s\n", new_dir, strerror(errno));
		table->last_exit_status = 1;
	}
	else
	{
		table->last_exit_status = 0;
	}
}

void	exe_cd_tilde(char *path, t_cmnd_tbl *table, t_fd *fd)
{
	char	*new_dir;

	new_dir = build_new_dir(path);
	if (!new_dir)
	{
		restore_fd(fd);
		ft_printf("minishell: cd: HOME not set\n");
		table->last_exit_status = 1;
		return ;
	}
	if (!new_dir)
	{
		restore_fd(fd);
		ft_printf("minishell: cd: Cannot allocate memory\n");
		table->last_exit_status = 1;
		return ;
	}
	change_to_new_dir(new_dir, fd, table);
	free(new_dir);
}

void	exe_cd_bare(char *path, t_cmnd_tbl *table, t_fd *fd)
{
	if (chdir(path) != 0)
	{
		restore_fd(fd);
		ft_printf("minishell: cd: %s: %s\n", path, strerror(errno));
		table->last_exit_status = 1;
	}
	else
	{
		table->last_exit_status = 0;
	}
	return ;
}

void	set_env_var(t_cmnd_tbl *table, char *name, char *value, t_fd *fd)
{
	t_env_list	*current;
	t_env_list	*prev;
	t_env_list	*new_node;

	current = table->envp;
	prev = NULL;
	while (current && !is_match(current->name, name))
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		free(current->value);
		current->value = ft_strdup(value);
	}
	else
	{
		new_node = create_node(name, value);
		if (new_node == NULL)
		{
			restore_fd(fd);
			ft_printf("minishell: cd: Cannot allocate memory\n");
			return ;
		}
		if (prev)
			prev->next = new_node;
		else
			table->envp = new_node;
	}
}

void	update_env(t_cmnd_tbl *table, t_fd *fd)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == NULL)
	{
		restore_fd(fd);
		ft_printf("minishell: cd: %s\n", strerror(errno));
		table->last_exit_status = 1;
		return ;
	}
	set_env_var(table, "PWD", dir, fd);
	return (free(dir));
}

void	exe_cd(t_command *cmd, t_cmnd_tbl *table, t_fd *fd)
{
	char	*path;

	if (cmd->args == NULL || cmd->args[0] == NULL)
	{
		exe_cd_home(table, fd);
		return ;
	}
	if (cmd->args[1] != NULL)
	{
		restore_fd(fd);
		ft_printf("minishell: cd: too many arguments\n");
		table->last_exit_status = 1;
		return ;
	}
	else
	{
		path = cmd->args[0];
		if (path[0] == '~')
		{
			exe_cd_tilde(path, table, fd);
		}
		else
		{
			exe_cd_bare(path, table, fd);
		}
	}
	update_env(table, fd);
}
