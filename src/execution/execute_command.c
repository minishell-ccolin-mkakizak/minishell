/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:57:08 by minoka            #+#    #+#             */
/*   Updated: 2024/11/18 15:53:54 by mkakizak         ###   ########.fr       */
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

char	*find_path(char *cmd, char *envp[])
{
	char	**path_arr;
	char	*path_str;
	char	*path;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
		{
			path_str = ft_strnstr(envp[i], "PATH=", 5);
			break ;
		}
		i++;
	}
	path_str = ft_strtrim(path_str, "PATH=");
	path_arr = ft_split(path_str, ':');
	free(path_str);
	path = validate_path(path_arr, cmd);
	if (path)
		return (path);
	return (ft_free_all(path_arr), NULL);
}

int	execute_cmd(t_command *cmd, char *envp[], int is_child)
{
	char	**cmd_arr;
	char	*path;

	// print_command(cmd);
	// ft_printf("[non-builtin]is_child is%d\n", is_child);

	path = find_path(cmd->args[0], envp);
	if (!path)
	{
		// need to handle errors here
		// free_all(cmd_arr);
		// free(path);
		throw_error("bash: command not found", 127, 0);
	}
	if (execve(path, cmd->args, envp) == -1)
	{
		ft_free_all(cmd->args);
		free(path);
		throw_error("bash: execution went worng", EXIT_FAILURE, 0);
	}
	return (0);
}