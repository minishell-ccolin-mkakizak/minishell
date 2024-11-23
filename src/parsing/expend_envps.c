/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_envps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:54:57 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/23 16:05:48 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expend_envp(char *str, t_env_list *envp)
{
	int	name_len;

	while (envp)
	{
		name_len = ft_strlen(envp->name);
		if (name_len == ft_strlen(str) && !ft_strncmp(envp->name, str,
				name_len))
		{
			free(str);
			str = ft_strdup(envp->value);
			break ;
		}
		envp = envp->next;
	}
	if (!envp)
	{
		free(str);
		str = ft_strdup("");
	}
	return (str);
}

char	*replace_substring_with_envp(char *str, int start, int end,
		t_env_list *envp)
{
	char	*prefix;
	char	*variable;
	char	*suffix;

	prefix = ft_substr(str, 0, start);
	variable = expend_envp(ft_substr(str, start + 1, end - start), envp);
	suffix = ft_substr(str, end + 1, ft_strlen(str));
	free(str);
	if (prefix[0] != 0)
		str = ft_strjoin(prefix, variable);
	else
		str = ft_strdup(variable);
	if (suffix[0] != 0)
		str = ft_strjoin(str, suffix);
	free(prefix);
	free(variable);
	free(suffix);
	return (str);
}

static char	*process_env_var(char *str, t_env_list *envp, int start)
{
	int	end;

	end = start + 1;
	while (str[start] && is_valid_key_char(str[end], FALSE))
		end++;
	return (replace_substring_with_envp(str, start, end - 1, envp));
}

char	*find_envps(char *str, t_env_list *envp, int is_command)
{
	int	i;
	int	in_squote;
	int	in_dquote;

	i = 0;
	in_squote = 0;
	in_dquote = 0;
	while (str[i])
	{
		if (is_command && handle_quotes(str[i], &in_squote, &in_dquote))
		{
			i++;
			continue ;
		}
		if (str[i] == '$' && is_valid_key_char(str[i + 1], TRUE) && (!is_command
				|| !in_squote))
		{
			str = process_env_var(str, envp, i);
			i = 0;
		}
		else
			i++;
	}
	return (str);
}

void	expend_envps(t_token *token, t_env_list *envp)
{
	while (token)
	{
		if (token && token->type == HEREDOC)
			token = token->next->next;
		if (token && token->type == ENVP
			|| token->type == STRING_TYPE | token->type == DOUBLE_QUOTE)
			token->token = find_envps(token->token, envp, FALSE);
		token = token->next;
	}
}
