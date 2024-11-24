/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:09:00 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/24 12:57:39 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*=============================================================================
Builds the command token. Contrary to the other tokens, the command envps need
to be expended at that point to determine if the parser should look for another
command.
The reason why is that bash can use a double quoted non existing env as the
command. But if it is not quoted, the token is discarded and the parser 
continues looking for a command.
ex: 
	$AAAAA => token discarded.
	"$AAAA" => command is set to an empty string.
=============================================================================*/
int	command_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int	j;
	int	is_quoted_string;

	is_quoted_string = FALSE;
	j = i;
	while (input[j] && input[j] != ' ')
	{
		if (input[j] == '\'' || input[i] == '\"')
			go_to_end_of_quotes(input, &j, input[j]);
		j++;
	}
	token->token = ft_substr(input, i, j - i);
	i = j;
	token->type = COMMAND;
	token->token = expend_command_envps(token->token, lx_dt->envp,
			&is_quoted_string);
	if (!is_quoted_string && token->token[0] == 0)
	{
		free(token->token);
		return (tokenize(token, input, lx_dt, i));
	}
	lx_dt->expecting_command = FALSE;
	return (next_token(token, input, lx_dt, i));
}
