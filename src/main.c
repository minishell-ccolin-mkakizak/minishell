/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/03 07:01:56 by minoka           ###   ########.fr       */
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

int	main(void)
{
	char	*user;
	char	*path;
	char	*current_dir;
	int		exit;

	chdir(getenv("HOME"));
	user = getenv("USER");
	while (1)
	{
		path = getcwd(NULL, 0);
		current_dir = get_last_word(path, '/');
		ft_printf("%s@minishell:%s$ ", user, current_dir);
		free(path);
		free(current_dir);
		exit = minishell(clear_command(get_next_line(1)));
		if (exit)
			break ;
	}
	ft_printf("Exiting...\n");
}
