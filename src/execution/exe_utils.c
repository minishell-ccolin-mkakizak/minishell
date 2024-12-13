/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:17:15 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/13 12:34:39 by ccolin           ###   ########.fr       */
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

void	print_here_doc_error(char *delimiter)
{
	printf("\n");
	printf("minishell: warning: Here-document ");
	printf("delimited by end-of-file (wanted `%s')\n", delimiter);
	return ;
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		return (FALSE);
	}
	return (S_ISDIR(path_stat.st_mode));
}

int	is_path(const char *command)
{
	struct stat	sb;
	char		*str;

	if (stat(command, &sb) == 0 && sb.st_mode & S_IXUSR)
		return (TRUE);
	else
	{
		str = ft_strjoin("/", command);
		if (stat(str, &sb) == 0 && sb.st_mode & S_IXUSR)
		{
			free(str);
			return (TRUE);
		}
		free(str);
	}
	return (FALSE);
}
