/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:16 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/20 12:48:33 by ccolin           ###   ########.fr       */
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
	ft_printf("\ninput =\n\t\t|%s|", input);
	ft_printf("\ncleared input =\n\t\t|%s|\n", new_input);
	return (new_input);
}

void	print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		printf("Token %d: %s\n", i, tokens[i]);
		i++;
	}
}

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

char	**add_token(char **tokens, char *input, int start, int *i)
{
	if (input[*i] == ' ')
		tokens = add_str_to_arr(tokens, ft_substr(input, start, *i - start));
	return (tokens);
}

char	**tokenize(char *input, int i)
{
	char	**tokens;
	int		start;

	ft_printf("Starting tokenization of string \"%s\"\n", input);
	tokens = NULL;
	start = i;
	while (input[i])
	{
		skip_over_quotes(input, &i);
		if (ft_strchr(" |<>", input[i]))
		{
			ft_printf("string to add = %s, start = %d, end = %d\n", input, start, i);
			tokens = add_token(tokens, input, start, &i);
			start = i + 1;
		}
		i++;
	}
	if (start < i)
	{
		ft_printf("Adding last token, string to add = %s, start = %d, end = %d\n", input, start, i);
		tokens = add_str_to_arr(tokens, ft_substr(input, start, i - start));
	}
	print_tokens(tokens);
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
