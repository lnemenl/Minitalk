/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:29:46 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/10/28 16:30:36 by rkhakimu         ###   ########.fr       */
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
		usleep(100);
		i++;
	}
}

char	*allocate_message(int ac, char **av)
{
	int		i;
	int		len;
	char	*message;
	
	i = 2;
	len = 0;
	while (i < ac)
	{
		len += ft_strlen(av[i]) + 1;
		i++;
	}
	message = (char *)malloc(len + 1);
	if (!message)
		handle_error("Error: Memory allocation failed");
	message[0] = '\0';
	return (message);
}

void	combine_arguments(char *message, int ac, char **av)
{
	int	i;

	i = 2;
	while(i < ac)
	{
		ft_strlcat(message, av[i], ft_strlen(message) + ft_strlen(av[i]) + 1);
		if (i < ac - 1)
			ft_strlcat(message, " ", ft_strlen(message) + 2);
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
	message = allocate_message(ac, av);
	combine_arguments(message, ac, av);
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_end_of_message(server_pid);
	free(message);
	return (0);
}
