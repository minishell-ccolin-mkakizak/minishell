/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   are_quotes_closed.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:05:09 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/20 22:51:15 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_end_quote(char *input, int *i, char c)
{
	while (input[*i])
	{
		(*i)++;
		if (input[*i] == c)
			return (0);
	}
	return (1);
}

char	*continue_input(char *input)
{
	char	*line;
	char	*new_input;
	char	*temp;

	line = NULL;
	while (!line)
		line = readline("> ");
	temp = ft_strjoin(input, "\n");
	free(input);
	new_input = ft_strjoin(temp, line);
	free(line);
	new_input = are_quotes_closed(new_input);
	return (new_input);
}

char	*are_quotes_closed(char *input)
{
	int		i;
	int		open;

	i = 0;
	open = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			open = find_end_quote(input, &i, '\'');
		if (input[i] == '"')
			open = find_end_quote(input, &i, '"');
		i++;
	}
	if (open)
		input = continue_input(input);
	if (!input)
		return (NULL);
	return (input);
}
