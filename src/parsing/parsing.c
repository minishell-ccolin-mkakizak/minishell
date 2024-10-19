/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:16 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/19 17:41:58 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clear_input(char *input)
{
	int		i;
	int		j;
	char	*new_input;

	i = 0;
	j = 0;
	new_input = ft_calloc(ft_strlen(input), sizeof(char));
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	while (input[i])
	{
		new_input[j++] = input[i++];
		if (input[i - 1] == ' ' || input[i - 1] == '\t')
		{
			while (input[i] == ' ' || input[i] == '\t')
				i++;
		}
	}
	if (new_input[j - 1] == ' ' || new_input[j] == '\t')
		while (new_input[j - 1] == ' ' || new_input[j] == '\t')
			j--;
	new_input[j] = '\0';
	ft_printf("\ninput = |%s|", input);
	ft_printf("\ninput = |%s|\n", new_input);
	return (new_input);
}

char	**tokenize(char *input, int i)
{
	return (NULL);
}

t_command_table	*parse(char *input)
{
	char	**tokens;

	input = are_quotes_closed(input);
	// input = is_pipe_defined(input);
	// input = is_next_command_defined(input);
	add_history(input);
	input = clear_input(input);
	tokens = tokenize(input, 0);
	// is_command_valid()
	return (NULL);
}

int	main_parsing(void)
{
	char			*prompt;
	char			*hostname;
	char			*input;
	char			**tokens;

	ft_printf("Starting parsing mode\n");
	hostname = get_hostname();
	chdir(getenv("HOME"));
	while (1)
	{
		prompt = build_prompt(hostname);
		input = readline(prompt);
		if (!input)
			break ;
		free(prompt);
		parse(input);
	}
	clear_history();
	free(hostname);
	ft_printf("Exiting...\n");
	return (0);
}
