/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkakizak <mkakizak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:00:00 by mkakizak          #+#    #+#             */
/*   Updated: 2024/11/22 16:15:44 by mkakizak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// extern volatile sig_atomic_t sig_received = 0;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\nReceived SIGINT (Ctrl+C)\n");
		// sig_received = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();

	}
	else if (sig == SIGQUIT)
	{
		ft_printf("\nReceived SIGQUIT (Ctrl+\\)\n");
		// sig_received = 2;
        // rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGTERM)
	{
		// sig_received = 3;
		ft_printf("\nReceived SIGTERM\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}

}


void init_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = &signal_handler;

	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
