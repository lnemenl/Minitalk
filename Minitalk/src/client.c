/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:29:46 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/10/28 14:49:53 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"

void	handle_error(const char *error_message)
{
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	exit(1);
}

void	send_char(pid_t server_pid, char c)
{
	int	bit;
	bit = 7;
	
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(100);
		bit--;
	}
}

void	send_end_of_message(pid_t server_pid)
{
	int	i;
	i = 0;
	
	while (i < 8)
	{
		kill(server_pid, SIGUSR1);
		usleep(100);
		i++;
	}
}

int	main(int ac, char **av)
{
	pid_t	server_pid;
	char	*message;
	
	if (ac != 3)
	{
		write(2, "Usage: ./client <server_pid> <message>\n", 39);
		return (1);
	}
	
	server_pid = ft_atoi(av[1]);
	message = av[2];
	while(*message)
	{
		send_char(server_pid, *message);
		message++;
	}
	send_end_of_message(server_pid);
	return (0);
}
