/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:29:46 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/10/28 19:16:11 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	handle_error(const char *error_message);

void	send_char(pid_t server_pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
		{
			if (kill(server_pid, SIGUSR2) == -1)
				handle_error("Error: Failed to send SIGUSR2");
		}
		else
		{
			if (kill(server_pid, SIGUSR1) == -1)
				handle_error("Error: Failed to send SIGUSR1");
		}
		usleep(300);
		bit--;
	}
}

void	send_end_of_message(pid_t server_pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (kill(server_pid, SIGUSR1) == -1)
			handle_error("Error: Failed to send end-of-message signal");
		usleep(300);
		i++;
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;
	char	*message;
	int		i;

	i = 0;
	if (ac < 3)
		handle_error("Usage: ./client <server_pid> <message>");
	server_pid = ft_atoi(av[1]);
	if (server_pid <= 0)
		handle_error("Error: Invalid PID");
	message = av[2];
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_end_of_message(server_pid);
	return (0);
}
