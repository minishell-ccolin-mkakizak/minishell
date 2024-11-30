/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/30 13:53:26 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	realloc_array(char ***array, int i, int j)
{
	char	**new_array;

	if (i > 0)
	{
		new_array = malloc(sizeof(char *) * (i + 2));
		if (!new_array)
			return (alloc_failed());
		while ((*array)[j])
		{
			new_array[j] = ft_strdup((*array)[j]);
			if (!new_array[j++])
				return (alloc_failed());
		}
		new_array[j] = NULL;
		new_array[j + 1] = NULL;
		ft_free_all(*array);
		*array = new_array;
		return (0);
	}
	*array = malloc(sizeof(char *) * 2);
	if (!*array)
		return (alloc_failed());
	(*array)[0] = NULL;
	(*array)[1] = NULL;
	return (0);
}

int	handle_input_operator(t_token **token, t_command *command)
{
	int	i;

	i = 0;
	if ((*token)->type == INPUT_TYPE)
	{
		while (command->input_file && command->input_file[i])
			i++;
		if (realloc_array(&command->input_file, i, 0))
			return (ALLOCATION_FAIL);
		*token = (*token)->next;
		command->input_file[i] = ft_strdup((*token)->token);
		*token = (*token)->next;
	}
	return (0);
}

int	handle_output_append_operator(t_token **token, t_command *command)
{
	int	i;

	i = 0;
	if ((*token)->type == OUTPUT_TYPE)
	{
		while (command->output_file && command->output_file[i])
			i++;
		if (realloc_array(&command->output_file, i, 0))
			return (ALLOCATION_FAIL);
		*token = (*token)->next;
		command->output_file[i] = ft_strdup((*token)->token);
		*token = (*token)->next;
	}
	else if ((*token)->type == APPEND)
	{
		while (command->append && command->append[i])
			i++;
		if (realloc_array(&command->append, i, 0))
			return (ALLOCATION_FAIL);
		*token = (*token)->next;
		command->append[i] = ft_strdup((*token)->token);
		*token = (*token)->next;
	}
	return (0);
}

int	handle_heredoc_operator(t_token **token, t_command *command)
{
	int	i;

	i = 0;
	if ((*token)->type == HEREDOC)
	{
		while (command->heredoc_delimiter && command->heredoc_delimiter[i])
			i++;
		if (realloc_array(&command->heredoc_delimiter, i, 0))
			return (ALLOCATION_FAIL);
		*token = (*token)->next;
		command->heredoc_delimiter[i] = ft_strdup((*token)->token);
		*token = (*token)->next;
	}
	return (0);
}
