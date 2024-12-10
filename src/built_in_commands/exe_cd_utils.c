/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:09:16 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 16:39:09 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

t_env_list	*find_env_node(t_env_list *envp, char *name, t_env_list **prev)
{
	*prev = NULL;
	while (envp && !is_match(envp->name, name))
	{
		*prev = envp;
		envp = envp->next;
	}
	return (envp);
}

void	set_env_var(t_cmnd_tbl *table, char *name, char *value, t_fd *fd)
{
	t_env_list	*current;
	t_env_list	*prev;
	t_env_list	*new_node;

	current = find_env_node(table->envp, name, &prev);
	if (current)
	{
		free(current->value);
		current->value = ft_strdup(value);
		return ;
	}
	new_node = create_node(name, value);
	if (new_node)
	{
		if (prev)
			prev->next = new_node;
		else
			table->envp = new_node;
	}
	else
	{
		restore_fd(fd);
		ft_printf("minishell: cd: Cannot allocate memory\n");
	}
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
