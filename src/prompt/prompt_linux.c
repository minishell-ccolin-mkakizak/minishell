/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_linux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:23:45 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/29 16:51:49 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Retrieves the hostname for Linux */
char	*get_linux_hostname(void)
{
	int		fd;
	char	*hostname;
	char	*temp;

	fd = open(HOSTNAME_LINUX, O_RDONLY);
	if (fd == -1)
		return (ft_strdup("hostname"));
	temp = get_next_line(fd);
	hostname = ft_strdup(temp);
	free(temp);
	hostname[ft_strlen(hostname) - 1] = '\0';
	close(fd);
	return (hostname);
}

/* Extracts and returns the full path for Linux or just the current
directory for macOS */
char	*get_current_dir(const char *path, char delimiter)
{
	if (IS_LINUX)
	{
		if (ft_strncmp(path, getenv("HOME"), ft_strlen(getenv("HOME"))) == 0)
		{
			return (ft_strjoin("~", path + ft_strlen(getenv("HOME"))));
		}
		return (ft_strdup(path));
	}
	return (get_dir_mac(path, delimiter));
}

/* Retrieves the hostname for Linux or MacOS */
char	*get_hostname(void)
{
	int		fd;
	char	*hostname;

	if (IS_LINUX)
		return (get_linux_hostname());
	fd = open(HSTNM_MAC, O_RDONLY);
	if (fd == -1)
		return (ft_strdup("hostname"));
	hostname = extract_mac_hostname(fd);
	close(fd);
	return (hostname);
}

/* Returns the prompt suffix based on the user and platform */
char	*get_prompt_suffix(void)
{
	if (ft_strncmp("root", getenv("USER"), 4) == 0)
	{
		if (IS_LINUX)
			return ("# ");
		return (" root# ");
	}
	if (IS_LINUX)
		return ("$ ");
	return (" % ");
}

/* Determines the colon or space separator for Linux or macOS */
char	*colon_or_space(void)
{
	if (IS_LINUX)
		return (":");
	return (" ");
}
