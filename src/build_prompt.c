/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:18:15 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/05 11:18:40 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Extracts and returns the current directory name from the full path */
char	*get_current_dir(const char *path, char delimiter)
{	
	if (ft_strncmp(path, getenv("HOME"), ft_strlen(path)) == 0)
		return (ft_strdup("~"));
	const char *last_delim = ft_strrchr(path, delimiter);
	if (last_delim != NULL)
	{
			return (ft_strdup(last_delim + 1));
	}
	else
		return ft_strdup(path);
}

char	*get_hostname(void)
{
	int		fd;
	char	*hostname;
	
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
	{
		perror("Could not find hostname file (Ignore this error if on macOS)");
		hostname = ft_strdup("hostname");
		return (hostname);
	}
	hostname = get_next_line(fd);
	hostname[ft_strlen(hostname) - 1] = '\0';
	return (hostname);
}

char	*get_prompt_suffix(void)
{
	if (ft_strncmp("root", getenv("USER"), 4) == 0)
		return ("# ");
	return ("$ ");
}

char	*build_prompt(char *hostname)
{
	char	*user;
	char	*path;
	char	*current_dir;
	char	*prompt_suffix;
	int		total_len;
	char	*prompt;

	user = getenv("USER");
	path = getcwd(NULL, 0);
	prompt_suffix = get_prompt_suffix();
	current_dir = get_current_dir(path, '/');
	total_len = ft_strlen(user) + ft_strlen(current_dir) \
		+ ft_strlen(hostname)+ ft_strlen(prompt_suffix) + 3;
	prompt = malloc(total_len);
	if (!prompt)
		return (NULL);
	ft_strlcpy(prompt, user, total_len);
	ft_strlcat(prompt, "@", total_len);
	ft_strlcat(prompt, hostname, total_len);
	ft_strlcat(prompt, ":", total_len);
	ft_strlcat(prompt, current_dir, total_len);
	ft_strlcat(prompt, prompt_suffix, total_len);
	free(path);
	free(current_dir);
	return (prompt);
}