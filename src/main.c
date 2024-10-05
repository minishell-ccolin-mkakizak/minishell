/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/05 10:22:39 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Replaces tabs with spaces and removes extra spaces, ensuring only
single spaces remain */
char	*clear_command(char *command)
{
	int		i;
	int		j;
	char	*cleaned;

	if (!command)
		return (NULL);
	if (command[0] == '\0')
		return (command);
	i = 0;
	j = 0;
	cleaned = (char *)malloc(sizeof(char) * (ft_strlen(command) + 1));
	if (!cleaned)
		return (NULL);
	while (command[i])
	{
		if (command[i] == '\t')
			command[i] = ' ';
		if (command[i] != ' ' || (j > 0 && cleaned[j - 1] != ' '))
			cleaned[j++] = command[i];
		i++;
	}
	cleaned[j] = '\0';
	free(command);
	return (cleaned);
}

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

int	main(void)
{
	char	*prompt;
	char	*hostname;
	int		exit;

	hostname = get_hostname();
	chdir(getenv("HOME"));
	while (1)
	{
		prompt = build_prompt(hostname);
		exit = minishell(clear_command(readline(prompt)));
		free(prompt);
		if (exit)
			break ;
	}
	clear_history();
	free(hostname);
	ft_printf("Exiting...\n");
}
