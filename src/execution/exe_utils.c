/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:17:15 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/10 15:24:16 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_match(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str1)) == 0)
		return (TRUE);
	else
		return (FALSE);
}

int	get_array_len(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i])
	{
		i++;
	}
	return (i);
}

int	print_str_arr(char **arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_printf("[%d]:%s\n", i, arr[i]);
		i++;
	}
	return (0);
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		return (FALSE);
	};
	return (S_ISDIR(path_stat.st_mode));
}

int	is_path(const char *command)
{
	struct stat sb;

	if (stat(command, &sb) == 0 && sb.st_mode & S_IXUSR)
		return (TRUE);
	return (FALSE);
}