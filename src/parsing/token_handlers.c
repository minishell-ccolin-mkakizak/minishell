/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 17:37:49 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/16 17:38:51 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	single_quote_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int	j;

	j = ++i;
	while (input[j] && input[j] != '\'')
		j++;
	token->token = ft_substr(input, i, j - i);
	i = j;
	token->type = lx_dt->next_token_type;
	i++;
	next_token(token, input, lx_dt, i);
}

void	double_quote_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int	j;

	j = ++i;
	while (input[j] && input[j] != '\"')
		j++;
	token->token = ft_substr(input, i, j - i);
	i = j;
	token->type = lx_dt->next_token_type;
	i++;
	next_token(token, input, lx_dt, i);
}

void	envp_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int	j;

	j = ++i;
	while (is_valid_key_char(input[j], FALSE))
		j++;
	token->token = ft_substr(input, i, j - i);
	i = j;
	token->type = lx_dt->next_token_type;
	next_token(token, input, lx_dt, i);
}

void	dbl_char_opr_tok(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	token->token = malloc(sizeof(char) * (2 + 1));
	if (!token->token)
		return ;
	token->token[0] = input[i];
	token->token[1] = input[i];
	token->token[2] = '\0';
	token->type = lx_dt->next_token_type;
	i = i + 2;
	next_token(token, input, lx_dt, i);
}

void	sngl_char_opr_tok(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	token->token = malloc(sizeof(char) * (1 + 1));
	if (!token->token)
		return ;
	token->token[0] = input[i];
	token->token[1] = '\0';
	token->type = lx_dt->next_token_type;
	i++;
	next_token(token, input, lx_dt, i);
}

void	string_token(t_token *token, char *input, t_lx_dt *lx_dt, int i)
{
	int j;

	j = i;
	while (input[j] && !is_delimiter(input, j))
		j++;
	token->token = ft_substr(input, i, j - i);
	i = j;
	token->type = lx_dt->next_token_type;
	next_token(token, input, lx_dt, i);
}