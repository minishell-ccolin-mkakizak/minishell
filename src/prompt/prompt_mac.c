/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_mac.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:23:32 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/23 14:09:19 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function to handle macOS case in get_current_dir */
char	*get_dir_mac(const char *path, char delimiter)
{
	const char	*last_delim;

	if (ft_strncmp(path, getenv("HOME"), ft_strlen(path)) == 0)
		return (ft_strdup("~"));
	last_delim = ft_strrchr(path, delimiter);
	if (last_delim != NULL)
		return (ft_strdup(last_delim + 1));
	return (ft_strdup(path));
}

/* Extracts the Mac hostname from a configuration file */
char	*extract_mac_hostname(int fd)
{
	char	*line;
	char	*hostname;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strnstr(line, "LocalHostName", ft_strlen(line)))
		{
			free(line);
			line = get_next_line(fd);
			break ;
		}
		free(line);
	}
	hostname = parse_mac_hostname(line);
	free(line);
	return (hostname);
}

/* Parses the hostname from the Mac config line */
char	*parse_mac_hostname(char *line)
{
	char	*temp;
	char	*end;
	char	*hostname;

	temp = ft_strnstr(line, "<string>", ft_strlen(line)) + 8;
	end = ft_strnstr(temp, "</string>", ft_strlen(temp));
	*end = '\0';
	hostname = ft_strdup(temp);
	return (hostname);
}
