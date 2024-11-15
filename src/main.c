/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minoka <minoka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/30 18:02:43 by minoka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_envp(char **envp)
{
	int		i;
	char	**copy;

	i = 0;
	while (envp[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

int	main(int argc, char **argv, char **envp)
{
	int			mode;
	char		**envp_copy;

	(void)argc;
	(void)argv;
	envp_copy = copy_envp(envp);
	mode = 2;
	while (mode != 0 && mode != 1)
	{
		ft_printf("%s", "Execution mode: 0\nParsing mode: 1\n");
		scanf("%d", &mode);
	}

	if (!mode)
	{
		main_execution(envp_copy);
		ft_free_all(envp_copy);
		return (0);
	}

	// main_parsing(envp_copy);
	return (0);
}
