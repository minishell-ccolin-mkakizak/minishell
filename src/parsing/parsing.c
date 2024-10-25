/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:32:16 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/25 12:36:37 by ccolin           ###   ########.fr       */
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
	ft_printf("\n----------\ninput =\n\t\t|%s|", input);
	ft_printf("\n----------\ncleared input =\n\t\t|%s|", new_input);
	return (new_input);
}

void	lex(char *input, char **envp, t_cmnd_tbl command_table)
{
	char		**p_toks;
	// t_token	*tokens;
	//sometype	ast;

	input = are_quotes_closed(input);
	// input = is_pipe_defined(input);
	// input = is_next_command_defined(input);
	ft_printf("----------\nENVPs\n");
	print_envp(envp);
	input = clear_input(input);
	p_toks = p_tokize(input, 0);
	ft_printf("\n----------\np_tokS\n");
	print_p_toks(p_toks);
	//tokens = tokenize(p_toks);
	//ast = build_ast(tokens);
	//command_table = build_command_table(ast);
	add_history(input);
	free(input);
	return ;
}

int	main_parsing(char **envp)
{
	char			*prompt;
	char			*hostname;
	char			*input;
	char			**p_toks;
	t_cmnd_tbl	command_table;

	ft_printf("Starting parsing mode\n");
	hostname = get_hostname();
	chdir(getenv("HOME"));
	while (1)
	{
		prompt = build_prompt(hostname);
		input = readline(prompt);
		if (!input)
		{
			free(prompt);
			break ;
		}
		free(prompt);
		lex(input, envp, command_table);
	}
	clear_history();
	free(hostname);
	ft_printf("Exiting...\n");
	return (0);
}
//need to copy envp
