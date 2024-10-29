/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:29:40 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/10/30 00:12:06 by rkhakimu         ###   ########.fr       */
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
	(void)info;
	(void)ucontext;

	if (signum == SIGUSR1)
		current_char = (current_char << 1);
	else if (signum == SIGUSR2)
		current_char = (current_char << 1) | 1;
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
}

int	main(void)
{
	pid_t	pid;
	struct	sigaction act;

	pid = getpid();
	if (pid <= 0)
		handle_error("Error: Unable to receive PID");
	ft_printf("Server PID: %d\n", pid);
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		handle_error("Error: Failed to set SIGUSR1 handler");
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		handle_error("Error: Failed to set SIGUSR2 handler");
	while (1)
		pause();
	return (0);
}
