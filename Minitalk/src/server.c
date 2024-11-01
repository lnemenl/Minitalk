/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:29:40 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/11/01 08:32:38 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include "ft_printf.h"

void	handle_error(const char *error_message);

void	signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	static int	bit_count;
	static char	current_char;
	pid_t		client_pid;

	(void)ucontext;
	client_pid = info->si_pid;
	current_char = (current_char << 1) | (signum == SIGUSR2);
	bit_count++;
	if (bit_count == 8)
	{
		if (current_char == '\0')
			write(1, "\n", 1);
		else
			write(1, &current_char, 1);
		bit_count = 0;
		current_char = 0;
	}
	if (kill(client_pid, SIGUSR1) == -1)
		handle_error("Error: Failed to send acknowledgment to client");
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("Server PID: %d\n", getpid());
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		handle_error("Error: Failed to set SIGUSR1 handler");
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		handle_error("Error: Failed to set SIGUSR2 handler");
	while (1)
		pause();
	return (0);
}
