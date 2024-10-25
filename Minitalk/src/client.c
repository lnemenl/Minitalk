/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:29:46 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/10/25 13:04:59 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <./lib/Libft/libft.h>
#include <./lib/Libft/ft_printf.h>

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
		kill(server_pid, SIGUSR1);
		usleep(100);
		message++;
	}
	return (0);
}

