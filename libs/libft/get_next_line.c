/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:41:24 by minokakakiz       #+#    #+#             */
/*   Updated: 2024/11/18 15:41:50 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char *sttc_str, char *buffer)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc((gnl_strlen(sttc_str) + gnl_strlen(buffer) + 1)
			* sizeof(char));
	if (res == NULL)
	{
		free(sttc_str);
		return (NULL);
	}
	while (sttc_str[i] != '\0')
	{
		res[i] = sttc_str[i];
		i++;
	}
	while (buffer[j] != '\0')
	{
		res[i + j] = buffer[j];
		j++;
	}
	res[i + j] = '\0';
	return (free(sttc_str), res);
}

char	*get_new_string(int fd, char *sttc_str)
{
	char	*buffer;
	int		bytes;
	char	*result;

	bytes = 1;
	if (init(sttc_str, &buffer, &result) == -1)
		return (NULL);
	while (check_for_new_line(result) == 0 && (bytes != 0))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			return (free(sttc_str), free(result), free(buffer), NULL);
		}
		buffer[bytes] = '\0';
		result = gnl_strjoin(result, buffer);
		if (result == NULL)
		{
			return (free(buffer), NULL);
		}
	}
	if (clean_up(&sttc_str, &buffer, &result, &bytes) == -1)
		return (NULL);
	return (sttc_str);
}

char	*get_one_line(char *str)
{
	int		len;
	int		i;
	char	*result;

	len = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[len] != '\0' && str[len] != '\n')
	{
		len++;
	}
	i = 0;
	result = malloc(sizeof(char) * len + 2);
	if (result == NULL)
		return (NULL);
	while (i <= len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*trim_string(int n, char *str)
{
	int		i;
	int		len;
	char	*result;

	if (n == 0 || str == NULL)
	{
		free(str);
		return (NULL);
	}
	len = gnl_strlen(str) - n;
	i = 0;
	result = malloc(sizeof(char) * len + 1);
	if (result == NULL)
	{
		free(str);
		return (NULL);
	}
	while (i < len)
	{
		result[i] = str[n + i];
		i++;
	}
	result[i] = '\0';
	return (free(str), result);
}

char	*get_next_line(int fd)
{
	static char	*sttc_str[1024];
	char		*result;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	sttc_str[fd] = get_new_string(fd, sttc_str[fd]);
	if (sttc_str[fd] == NULL)
		return (NULL);
	result = get_one_line(sttc_str[fd]);
	if (result == NULL)
		return (NULL);
	sttc_str[fd] = trim_string(gnl_strlen(result), sttc_str[fd]);
	if (sttc_str[fd] == NULL)
		return (NULL);
	return (result);
}
