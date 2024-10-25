/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:28:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/25 10:03:54 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_over_quotes(char *input, int *i)
{
	if (input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] != '\'')
			(*i)++;
	}
	if (input[*i] == '"')
	{
		(*i)++;
		while (input[*i] != '"')
			(*i)++;
	}
}

int	array_size(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

char	**add_str_to_arr(char **array, char *new_string)
{
	int		i;
	int		size;
	char	**new_array;

	i = 0;
	size = array_size(array);
	new_array = malloc(sizeof(char *) * (size + 2));
	if (!new_array)
		return (NULL);
	while (i < size)
	{
		new_array[i] = array[i];
		i++;
	}
	new_array[size] = new_string;
	new_array[size + 1] = NULL;
	free (array);
	return (new_array);
}

char	*char_to_string(char c)
{
	char	*str;

	str = (char *)malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*char_to_double_string(char c)
{
	char	*str;

	str = (char *)malloc(3 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = c;
	str[2] = '\0';
	return (str);
}
