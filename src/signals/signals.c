/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolin <ccolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:00:00 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/12 18:06:11 by ccolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_global = 130;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGTERM)
	{
		exit(EXIT_SUCCESS);
	}
}

void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(130);
	}
	else if (sig == SIGTERM)
	{
		exit(EXIT_SUCCESS);
	}
}

int	init_signals(int is_child)
{	
	struct sigaction	sa;

	if (is_child)
	{
		sa.sa_handler = child_signal_handler;
	}
	else
	{
		sa.sa_handler = signal_handler;
	}
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGTERM, &sa, NULL);
	return (0);
}

int	ignore_signals(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		return (-1);
	if (signal(SIGTERM, SIG_IGN) == SIG_ERR)
		return (-1);
	return (0);
}
