/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_envps_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:02:55 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/24 12:39:01 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*=============================================================================
Removes quotes from the command token. if the length of the string with and
without quotes is not the same, is_quoted_string is TRUE.
=============================================================================*/
char	*remove_quotes(char *command, int i, int j, int *is_quoted_string)
{
	char	*new_str;
	char	c;
	int		len;

	len = quoteless_strlen(command, 0, 0);
	if (len != ft_strlen(command))
		*is_quoted_string = TRUE;
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '"')
		{
			c = command[i++];
			while (command[i] && command[i] != c)
				new_str[j++] = command[i++];
			if (command[i])
				i++;
		}
		else
			new_str[j++] = command[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

/*=============================================================================
Used to determine how much to allocated for the creation of a unquoted string
from a quoted string.
=============================================================================*/
int	quoteless_strlen(char *str, int i, int j)
{
	char	c;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
			{
				j++;
				i++;
			}
			if (str[i])
				i++;
		}
		else
		{
			j++;
			i++;
		}
	}
	return (j);
}

char	*expend_command_envps(char *command, t_env_list *envp,
		int *is_quoted_string)
{
	command = find_envps(command, envp, TRUE);
	command = remove_quotes(command, 0, 0, is_quoted_string);
	return (command);
}
