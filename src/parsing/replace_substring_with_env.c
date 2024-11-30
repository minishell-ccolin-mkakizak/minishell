/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_substring_with_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 13:38:01 by ccolin            #+#    #+#             */
/*   Updated: 2024/11/30 13:56:39 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_substrings(char *temp, char *prefix, char *variable, char *suffix)
{
	free(temp);
	free(prefix);
	free(variable);
	free(suffix);
}

/*=============================================================================
Cuts the string in 3, the prefix, the env inside the string and the suffix.
expends the env and puts the original string back together.
=============================================================================*/
char	*replace_substring_with_envp(char *str, int start, int end,
		t_env_list *envp)
{
	char	*prefix;
	char	*variable;
	char	*suffix;
	char	*temp;

	prefix = ft_substr(str, 0, start);
	variable = expend_envp(ft_substr(str, start + 1, end - start), envp);
	suffix = ft_substr(str, end + 1, ft_strlen(str));
	free(str);
	if (prefix[0] != 0)
		temp = ft_strjoin(prefix, variable);
	else
		temp = ft_strdup(variable);
	if (suffix[0] != 0)
		str = ft_strjoin(temp, suffix);
	else
	{
		free(prefix);
		free(variable);
		free(suffix);
		return (temp);
	}
	free_substrings(temp, prefix, variable, suffix);
	return (str);
}

char	*replace_substring_with_exit_status(char *str, int start, int end,
		int last_exit_status)
{
	char	*prefix;
	char	*variable;
	char	*suffix;
	char	*temp;

	prefix = ft_substr(str, 0, start);
	variable = ft_itoa(last_exit_status);
	suffix = ft_substr(str, end + 1, ft_strlen(str));
	free(str);
	if (prefix[0] != 0)
		temp = ft_strjoin(prefix, variable);
	else
		temp = ft_strdup(variable);
	if (suffix[0] != 0)
		str = ft_strjoin(temp, suffix);
	else
	{
		free(prefix);
		free(variable);
		free(suffix);
		return (temp);
	}
	free_substrings(temp, prefix, variable, suffix);
	return (str);
}
