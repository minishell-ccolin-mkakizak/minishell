/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:00:00 by mkakizak          #+#    #+#             */
/*   Updated: 2024/12/02 15:35:45 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

volatile sig_atomic_t sig_received = 0;

// extern volatile sig_atomic_t sig_received = 0;
void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		// printf("SIGINT is: [%d]\n\n", sig);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		// printf("SIGQUIT is: [%d]\n\n", sig);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGTERM)
	{
		// printf("SIGTERM is: [%d]\n\n", sig);
		// write(STDOUT_FILENO, "\nReceived SIGTERM\n", 17);
		exit(EXIT_SUCCESS);
	}
}

void init_signals(void)
{	
	struct sigaction sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT,&sa, NULL);
	sigaction(SIGTERM,&sa, NULL);
}

