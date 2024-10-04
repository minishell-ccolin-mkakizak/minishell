/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 23:12:14 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/04 13:35:28 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_newline(char *command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	i--;
	command[i] = '\0';
	return (command);
}

int	array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

int	count_delimiters(char *input, char *delimiter)
{
	int		count;
	char	*next_delim;
	int		delimiter_len;

	count = 0;
	delimiter_len = ft_strlen(delimiter);
	if (delimiter_len == 0)
		return (0);
	while ((next_delim = ft_strnstr(input, delimiter, ft_strlen(input))))
	{
		count++;
		input = next_delim + delimiter_len;
	}
	return (count);
}

/* Splits a string by a substring delimiter */
char	**split_by_string(char *input, char *delimiter)
{
	char	**result;
	char	*start;
	char	*next_delim;
	int		i;

	result = (char **)malloc(sizeof(char *) * (count_delimiters(input, delimiter) + 2));
	if (!result)
		return (NULL);
	start = input;
	i = 0;
	while ((next_delim = ft_strnstr(start, delimiter, ft_strlen(start))))
	{
		result[i] = ft_substr(start, 0, next_delim - start);
		start = next_delim + ft_strlen(delimiter);
		i++;
	}
	result[i] = ft_strdup(start);
	result[++i] = NULL;

	return (result);
}

/* Splits the input command into an array of arrays of words,
with each command group separated by '&&' */
char	***split_commands(char *input)
{
	char	**command_groups;
	char	***commands;
	int		i;

	// if (input[0] != '\n')
	// 	remove_newline(input);
	command_groups = split_by_string(input, "&&");
	if (!command_groups)
		return (NULL);
	commands = (char ***)malloc(sizeof(char **) * (array_len(command_groups) + 1));
	if (!commands)
		return (NULL);
	i = 0;
	while (command_groups[i])
	{
		commands[i] = ft_split(command_groups[i], ' ');
		i++;
	}
	commands[i] = NULL;
	free_all(command_groups);
	return (commands);
}