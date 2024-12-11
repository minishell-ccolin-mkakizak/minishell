/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/12/11 15:48:23 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*=============================================================================
The whole file is pretty self-explanatory but keep in mind that the int
next_token_type is initialized by tokenise before is calls those functions,
to know what function to call. That means that at this point in the process,
next_token_type is actually the type of the token currently being built and
not the next one.
If that makes any sense.
=============================================================================*/

int	quote_token(t_token *token, char **input, t_lx_dt *lx_dt, int i)
{
	int		j;
	char	c;

	c = (*input)[i];
	j = i;
	while (1)
	{
		j++;
		if (!(*input)[j])
			input = continue_input(input, ">");
		if ((*input)[j] == c)
			break ;
	}
	token->token = ft_substr(*input, i + 1, j - i - 1);
	i = j;
	token->type = lx_dt->next_token_type;
	i++;
	return (next_token(token, input, lx_dt, i));
}

int	envp_token(t_token *token, char **input, t_lx_dt *lx_dt, int i)
{
	int	j;

	j = i + 1;
	if ((*input)[j] == '?')
	{
		j++;
		token->token = ft_substr(*input, i, j - i);
	}
	else
	{
		while (is_valid_key_char((*input)[j], FALSE))
			j++;
		token->token = ft_substr(*input, i, j - i);
	}
	i = j;
	token->type = lx_dt->next_token_type;
	return (next_token(token, input, lx_dt, ++i));
}

int	dbl_char_opr_tok(t_token *token, char **input, t_lx_dt *lx_dt, int i)
{
	token->token = malloc(sizeof(char) * (2 + 1));
	if (!token->token)
		return (alloc_failed());
	token->token[0] = (*input)[i];
	token->token[1] = (*input)[i];
	token->token[2] = '\0';
	token->type = lx_dt->next_token_type;
	i = i + 2;
	return (next_token(token, input, lx_dt, i));
}

int	sngl_char_opr_tok(t_token *token, char **input, t_lx_dt *lx_dt, int i)
{
	token->token = malloc(sizeof(char) * (1 + 1));
	if (!token->token)
		return (alloc_failed());
	token->token[0] = (*input)[i];
	token->token[1] = '\0';
	token->type = lx_dt->next_token_type;
	i++;
	return (next_token(token, input, lx_dt, i));
}

int	string_token(t_token *token, char **input, t_lx_dt *lx_dt, int i)
{
	int	j;

	j = i;
	while ((*input)[j] && !is_delimiter(input, j))
		j++;
	token->token = ft_substr(*input, i, j - i);
	i = j;
	token->type = lx_dt->next_token_type;
	return (next_token(token, input, lx_dt, i));
}
