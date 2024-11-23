/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/23 14:08:38 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	realloc_array(char ***array, int i)
{
	char	**new_array;
	int		j;

	if (i > 0)
	{
		new_array = malloc(sizeof(char *) * (i + 2));
		if (!new_array)
			return ;
		j = 0;
		while ((*array)[j])
		{
			new_array[j] = ft_strdup((*array)[j]);
			j++;
		}
		new_array[j] = NULL;
		new_array[j + 1] = NULL;
		ft_free_all(*array);
		*array = new_array;
		return ;
	}
	*array = malloc(sizeof(char *) * 2);
	if (!*array)
		return ;
	(*array)[0] = NULL;
	(*array)[1] = NULL;
}

t_token	*handle_input_operator(t_token *token, t_command *command)
{
	if (token->type == INPUT_TYPE)
	{
		token = token->next;
		command->input_file = ft_strdup(token->token);
		token = token->next;
	}
	return (token);
}

t_token	*handle_output_append_operator(t_token *token, t_command *command)
{
	int	i;

	i = 0;
	if (token->type == OUTPUT_TYPE)
	{
		while (command->output_file && command->output_file[i])
			i++;
		realloc_array(&command->output_file, i);
		token = token->next;
		command->output_file[i] = ft_strdup(token->token);
		token = token->next;
	}
	else if (token->type == APPEND)
	{
		while (command->append && command->append[i])
			i++;
		realloc_array(&command->append, i);
		token = token->next;
		command->append[i] = ft_strdup(token->token);
		token = token->next;
	}
	return (token);
}

t_token	*handle_heredoc_operator(t_token *token, t_command *command)
{
	if (token->type == HEREDOC)
	{
		token = token->next;
		command->heredoc_delimiter = ft_strdup(token->token);
		token = token->next;
	}
	return (token);
}
