/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:00:00 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/11 15:53:44 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// extern volatile sig_atomic_t sig_received = 0;
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
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
	if(is_child)
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
