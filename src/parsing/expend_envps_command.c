/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_envps_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:02:55 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/10 17:49:37 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*=============================================================================
Copies the command into a new string while removing any quoted segments.
Handles single and double quotes, preserving only the contents inside them.
=============================================================================*/
static void	copy_without_quotes(const char *command, char *new_str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
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
}

/*=============================================================================
Removes quotes from the command token. If the length of the string with and
without quotes is not the same, is_quoted_string is set to TRUE.
=============================================================================*/
int	remove_quotes(char **command, int *is_quoted_string)
{
	char	*new_str;
	size_t	len;

	len = quoteless_strlen(*command, 0, 0);
	if (len != ft_strlen(*command))
		*is_quoted_string = TRUE;
	else
		return (0);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (alloc_failed());
	copy_without_quotes(*command, new_str);
	free(*command);
	*command = new_str;
	return (0);
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

int	expend_command_envps(char **command, t_lx_dt *lx_dt, int *is_quoted_string)
{
	*command = find_envps(*command, lx_dt->envp, TRUE, lx_dt->last_exit_status);
	if (remove_quotes(command, is_quoted_string))
		return (ALLOCATION_FAIL);
	return (0);
}
