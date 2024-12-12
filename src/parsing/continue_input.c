/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:03:40 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/11 17:54:40 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	go_to_end_of_quotes(char **input, int *j, char c)
{
	int	i;

	i = *j;
	while (1)
	{
		i++;
		if ((*input)[i] == c)
			break ;
		if (!(*input)[i])
		{
			printf("minishell: unexpected EOF while looking for matching `%c'\n", c);
			return (PARSING_ERROR);
		}
	}
	*j = i;
	return (0);
}

char	**is_input_after_pipe(char **input, int i)
{
	if ((*input)[i])
		i = skip_spaces_tabs(input, i);
	if ((*input)[i])
		return (input);
	printf("minishell: syntax error near unexpected token `|'\n");
	return (NULL);
}
