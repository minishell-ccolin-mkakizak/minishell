/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:16 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/15 13:46:16 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Replaces tabs with spaces and removes extra spaces, ensuring only
single spaces remain */
char	*clear_input(char *command)
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

void	replace_token_envp(char *token, char *key)
{
	free(token);
	token = ft_strdup(key);
}

int	compare_key_envp(char *token, char *key)
{
	int	i;

	i = 0;
	while (key[i] != '=')
		i++;
	if (strncmp(token, key, i))
	{
		replace_token_envp(token, key[i + 1]);
		return (1);
	}
	return (0);
}

char	**manage_envp(char **tokens, char **envp)
{
	int	i;
	int	j;
	int	replaced;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (token[i][0] == '$')
		{
			while (envp[j])
			{
				replaced = compare_key_envp(tokens[i], envp[j]);
				if (replaced)
					break ;
				j++;
				if (!envp[j])
					replace_key_envp(&tokens[i], "");
			}
		}
		i++;
	}
	return (tokens);
}

t_command_table	parsing(t_command_table table, char *input)
{
	char	**tokens;

	input = clear_input(input);
	tokens = ft_split(input, ' ');
	tokens = manage_envp(tokens, table->envp);
}
