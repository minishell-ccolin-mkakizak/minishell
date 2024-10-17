/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:26:02 by minoka            #+#    #+#             */
/*   Updated: 2024/10/14 15:04:09 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <minishell.h>

void	execute_cmd(char **cmd)
{
	// char	**cmd;
	if(fork() != 0)
		return ;
	char	*path;

	// cmd_arr = ft_split(cmd, ' ');
	// free(cmd);
	path = find_path(cmd[0]);

	if (!path)
	{
		free_all(cmd);
		free(path);
		throw_error("bash: command not found", 127, 0);
	}
	if (execve(path, cmd, NULL) == -1)
	{
		free_all(cmd);
		free(path);
		throw_error("bash: execution went worng", EXIT_FAILURE, 0);
	}
// 	return (0);
}

char	**parse_cmd(int argc, char *argv[])
{
	int		i;
	int		len;
	char	**res;

	if (argc != 5)
		throw_error("bash", EXIT_FAILURE, EINVAL);
	i = 0;
	len = argc - 3;
	res = ft_calloc(sizeof(char *), len + 1);
	if (!res)
		return (NULL);
	res[len] = NULL;
	while (i < len)
	{
		res[i] = ft_strdup(argv[i + 2]);
		if (res[i] == NULL)
		{
			free_all(res);
		}
		i++;
	}
	return (res);
}

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
				return (free_all(path_arr), cmd);
			else
				return (free_all(path_arr), NULL);
		}
		if (ft_strncmp(&path_arr[i][ft_strlen(path_arr[i]) - 1], "/", 1))
			tmp = ft_strjoin(path_arr[i], "/");
		else
			tmp = ft_strdup(path_arr[i]);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(path, X_OK))
			return (free_all(path_arr), path);
		free(path);
	}
	return (NULL);
}

char	*find_path(char *cmd)
{
	char	**path_arr;
	char	*path_str;
	char	*path;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	i = 0;
	// while (envp[i])
	// {
	// 	if (ft_strnstr(envp[i], "PATH=", 5))
	// 	{
	// 		path_str = ft_strnstr(envp[i], "PATH=", 5);
	// 		break ;
	// 	}
	// 	i++;
	// }
	path_str = getenv("PATH");
	// path_str = ft_strtrim(path_str, "PATH=");
	// printf("%s\n", path_str);

	path_arr = ft_split(path_str, ':');
	// free(path_str);
	path = validate_path(path_arr, cmd);
	if (path)
		return (path);
	return (free_all(path_arr), NULL);
}