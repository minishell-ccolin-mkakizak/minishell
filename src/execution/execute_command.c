/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:57:08 by minoka            #+#    #+#             */
/*   Updated: 2024/11/23 14:17:40 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*validate_path(char **path_arr, char *cmd)
{
	char	*path;
	int		i;
	char	*tmp;

	i = -1;
	while (path_arr[++i])
	{
		if (cmd[0] == '/')
		{
			if (!access(cmd, X_OK))
				return (ft_free_all(path_arr), cmd);
			else
				return (ft_free_all(path_arr), NULL);
		}
		if (ft_strncmp(&path_arr[i][ft_strlen(path_arr[i]) - 1], "/", 1))
			tmp = ft_strjoin(path_arr[i], "/");
		else
			tmp = ft_strdup(path_arr[i]);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(path, X_OK))
			return (ft_free_all(path_arr), path);
		free(path);
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env_list *envs)
{
	char	**path_arr;
	char	*path_str;
	char	*path;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	i = 0;
	path_str = get_env_var(envs, "PATH");
	if (path_str == NULL)
	{
		// errro handling for not finding paths:
	}
	path_arr = ft_split(path_str, ':');
	free(path_str);
	path = validate_path(path_arr, cmd);
	if (path)
		return (path);
	return (ft_free_all(path_arr), NULL);
}

char	**set_command(char *command, char **args)
{
	char	**res;
	int		args_count;
	int		i;

	i = 0;
	args_count = get_array_len(args);
	res = ft_calloc(sizeof(char *), args_count + 2);
	while (i <= args_count)
	{
		if (i == 0)
			res[i] = ft_strdup(command);
		else
			res[i] = ft_strdup(args[i - 1]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	execute_cmd(t_command *cmd, t_cmnd_tbl *table, int is_child, char *envp[])
{
	char	**set_array;
	char	*path;

	path = find_path(cmd->command, table->envp);
	set_array = set_command(cmd->command, cmd->args);
	if (!path)
	{
		// need to handle errors here
		// free_all(cmd_arr);
		// free(path);
		throw_error("minishell: command not found", 127, 0);
	}
	if (execve(path, set_array, envp) == -1)
	{
		ft_free_all(cmd->args);
		free(path);
		throw_error("minishell: execution went worng", EXIT_FAILURE, 0);
	}
	return (0);
}
