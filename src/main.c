/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/04 13:51:01 by ccolin           ###   ########.fr       */
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
char	*get_last_word(const char *str, char delimiter)
{
	const char *last_delim = ft_strrchr(str, delimiter);
	if (last_delim != NULL)
		return (ft_strdup(last_delim + 1));
	else
		return ft_strdup(str);
}

char	*build_prompt(void)
{
	char	*user;
	char	*path;
	char	*current_dir;
	char	*minishell;
	int		total_len;
	char	*prompt;

	user = getenv("USER");
	path = getcwd(NULL, 0);
	current_dir = get_last_word(path, '/');
	minishell = "minishell";
	total_len = ft_strlen(user) + ft_strlen(current_dir) \
		+ ft_strlen(minishell) + 5;
	prompt = malloc(total_len);
	if (!prompt)
		return (NULL);
	ft_strlcpy(prompt, user, total_len);
	ft_strlcat(prompt, "@", total_len);
	ft_strlcat(prompt, minishell, total_len);
	ft_strlcat(prompt, ":", total_len);
	ft_strlcat(prompt, current_dir, total_len);
	ft_strlcat(prompt, "$ ", total_len);
	free(path);
	free(current_dir);
	return (prompt);
}

int	main(void)
{
	char	*prompt;
	int		exit;
	
	chdir(getenv("HOME"));
	while (1)
	{
		prompt = build_prompt();
		exit = minishell(clear_command(readline(prompt)));
		free(prompt);
		if (exit)
			break ;
	}
	clear_history();
	ft_printf("Exiting...\n");
}
