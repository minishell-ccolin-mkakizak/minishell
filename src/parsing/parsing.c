/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:35:31 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/22 08:17:51 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*expend_string_envps(char *str, t_env_list *envp)
{
	return (str);
}

char	*expend_command_envps(char *cmd, t_env_list *envp)
{
	return (cmd);
}

char	*expend_double_quote_envps(char *str, t_env_list *envp)
{
	// int		i;
	// int		start;
	// int		index;
	// char	*key;
	// char	*prefix;
	// char	*suffix;
	
	// i = 0;
	// start = 0;
	// index = 0;
	// while (str[i])
	// {
	// 	if (str[i] == '$' && is_valid_key_char(str[i + 1], TRUE))
	// 	{
	// 		start = i++;
	// 		while (str[i] && is_valid_key_char(str[i], FALSE))
	// 			i++;
	// 		key = malloc(sizeof(char) * (i - start));
	// 		if (!key)
	// 			return (NULL);
	// 		start++;
	// 		while (start < i)
	// 		{
	// 			key[index++] = str[start++];
	// 		}
	// 		key[index] = '\0';
	// 	}
	// 	key = expend_envp_envps(key, envp);
	// }
	return (str);
}

char	*expend_envp_envps(char *str, t_env_list *envp)
{
	int		name_len;
	ft_printf("%s%c", str, 10); //debug
	while (envp)
	{
		name_len = ft_strlen(envp->name);
		if (name_len == ft_strlen(str) && !ft_strncmp(envp->name, str, name_len))
		{
			free(str);
			str = ft_strdup(envp->value);
			ft_printf("?%s%c", str, 10); //debug
			break ;
		}
		envp = envp->next;
	}
	if (!envp)
	{
		ft_printf("NOT FOUND%c", 10); //debug
		free(str);
		str = ft_strdup("");
	}
	return (str);
}

void	expend_envps(t_token *token, t_env_list *envp)
{
	while (token)
	{
		if (token->type == STRING_TYPE)
			token->token = expend_string_envps(token->token, envp);
		if (token->type == COMMAND)
			token->token = expend_envp_envps(token->token, envp);
		if (token->type == DOUBLE_QUOTE)
			token->token = expend_double_quote_envps(token->token, envp);
		if (token->type == ENVP)
			token->token = expend_envp_envps(token->token, envp);
		if (token->type == INPUT_TYPE || token->type == OUTPUT_TYPE || token->type == APPEND)
		{
			token = token->next;
			token->token = expend_string_envps(token->token, envp);
		}
		token = token->next;
	}
}

int	parse(char *input, t_cmnd_tbl *command_table)
{
	t_token	*token;
	t_lx_dt	*lx_dt;
	int		parser_error;

	lx_dt = malloc(sizeof(t_lx_dt));
	if (!lx_dt)
		return (0);
	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	init_lexer(&token, lx_dt, input);
	parser_error = tokenize(token, input, lx_dt, 0);
	expend_envps(token, command_table->envp);
	print_tokens(token);
	add_history(input);
	free(input);
	if (!parser_error)
	{
		build_command_table(token, command_table);
		print_cmnd_tbl(command_table);
	}
	free_parser_data(token, lx_dt);
	return (parser_error);
}
