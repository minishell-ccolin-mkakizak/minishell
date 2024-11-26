/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:03:40 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/26 13:20:38 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*=============================================================================
Called in case of  an unclosed quote or if the last token was a pipe.
=============================================================================*/
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
	if (!input)
		return (NULL);
	return (input);
}

/*=============================================================================
Used to skip over quoted text without ending the token if is encounters a 
separator character and prompt the user for input if the quote is unclosed.
=============================================================================*/
int	go_to_end_of_quotes(char *input, int *j, char c)
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
		if (!input)
			return (alloc_failed());
	}
	*j = i;
	return (0);
}

char	*continue_input_if_lst_tok_is_pipe(char *input, int i)
{
	i = skip_spaces_tabs(input, i);
	if (input[i])
		return (input);
	return (continue_input(input, ">"));
}
