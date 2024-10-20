/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:32:48 by ccolin            #+#    #+#             */
/*   Updated: 2024/10/20 19:06:34 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		mode;

	(void)argc;
	(void)argv;
	mode = 2;
	while (mode != 0 && mode != 1)
	{
		ft_printf("%s", "Execution mode: 0\nParsing mode: 1\n");
		scanf("%d", &mode);
	}
	if (!mode)
	{
		main_execution();
		return (0);
	}
	main_parsing(envp);
	return (0);
}
