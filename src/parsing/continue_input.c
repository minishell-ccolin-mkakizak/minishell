/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:03:40 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/23 15:03:49 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*continue_input(char *input, char *str)
{
	char	*line;
	char	*temp;

	line = readline(str);
	temp = ft_strjoin(input, "\n");
	free(input);
	input = ft_strjoin(temp, line);
	free(line);
	free(temp);
	return (input);
}

void	go_to_end_of_quotes(char *input, int *j, char c)
{
	int	i;

	i = *j;
	while (1)
	{
		i++;
		if (input[i] == c)
			break ;
		if (!input[i])
			input = continue_input(input, ">");
	}
	*j = i;
}

char	*continue_input_if_lst_tok_is_pipe(char *input, int i)
{
	i = skip_spaces_tabs(input, i);
	if (input[i])
		return (input);
	return (continue_input(input, ">"));
}
