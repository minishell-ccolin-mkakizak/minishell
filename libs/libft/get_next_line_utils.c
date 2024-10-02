/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 13:41:03 by minokakakiz       #+#    #+#             */
/*   Updated: 2024/07/11 18:02:08 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

int	check_for_new_line(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*gnl_strdup(const char *s)
{
	size_t	length;
	char	*cpy;
	int		i;

	length = ft_strlen(s);
	cpy = (char *)malloc(sizeof(char) * (length + 1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int	init(char *sttc_str, char **buffer, char **result)
{
	if (sttc_str == NULL)
		*result = gnl_strdup("");
	else
		*result = gnl_strdup(sttc_str);
	*buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*buffer == NULL)
	{
		free(*result);
		return (-1);
	}
	return (0);
}

int	clean_up(char **sttc_str, char **buffer, char **result, int *bytes)
{
	free(*sttc_str);
	*sttc_str = gnl_strdup(*result);
	free(*result);
	free(*buffer);
	if (*bytes == 0 && **sttc_str == '\0')
	{
		free(*sttc_str);
		return (-1);
	}
	return (0);
}
