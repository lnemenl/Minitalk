/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:29:46 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/11/04 06:43:37 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

volatile sig_atomic_t	g_acknowledgment_received = 0;

void	handle_error(const char *error_message);

void	ack_handler(int signum)
{
	if (signum == SIGUSR1)
		g_acknowledgment_received = 1;
}

void	send_bit(pid_t server_pid, int bit)
{
	g_acknowledgment_received = 0;
	if (bit)
	{
		if (kill(server_pid, SIGUSR2) == -1)
			handle_error("Error: Failed to send SIGUSR2");
	}
	else
	{
		if (kill(server_pid, SIGUSR1) == -1)
			handle_error("Error: Failed to send SIGUSR1");
	}
	while (!g_acknowledgment_received)
		usleep(50);
}

void	send_char(pid_t server_pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		send_bit(server_pid, (c >> bit) & 1);
		bit--;
	}
}

int	main(int ac, char **av)
{
	pid_t				server_pid;
	int					i;
	struct sigaction	act;

	i = 0;
	if (ac < 3)
		handle_error("Usage: ./client <server_pid> <message>");
	server_pid = ft_atoi(av[1]);
	if (server_pid <= 0)
		handle_error("Error: Invalid PID");
	sigemptyset(&act.sa_mask);
	act.sa_handler = ack_handler;
	act.sa_flags = SA_RESTART;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		handle_error("Error: Failed to set acknowledgement handler");
	if (kill(server_pid, 0) == -1)
		handle_error("Error: Invalid server PID");
	while (av[2][i] != '\0')
	{
		send_char(server_pid, av[2][i]);
		i++;
	}
	send_char(server_pid, '\0');
	return (0);
}
