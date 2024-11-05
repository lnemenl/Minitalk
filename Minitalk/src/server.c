/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:29:40 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/11/05 15:15:44 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"

volatile sig_atomic_t	g_current_client_pid = 0;
void	handle_error(const char *error_message, char **buffer);

void	expand_buffer(char **buffer, int *size, char c)
{
	char	*new_buffer;
	int		i;

	new_buffer = malloc(*size + 2);
	if (!new_buffer)
		handle_error("Error: Memory allocation failed", buffer);
	i = 0;
	while (i < *size)
	{
		new_buffer[i] = (*buffer)[i];
		i++;
	}
	new_buffer[*size] = c;
	new_buffer[*size + 1] = '\0';
	free(*buffer);
	*buffer = new_buffer;
	*size += 1;
}

void	process_character(int signum, char **buffer, int *bit_count, int *size)
{
	static char	current_char;

	current_char = (current_char << 1) | (signum == SIGUSR2);
	*bit_count += 1;
	if (*bit_count == 8)
	{
		if (current_char == '\0')
		{
			ft_printf("%s\n", *buffer);
			free(*buffer);
			*buffer = NULL;
			*size = 0;
		}
		else
			expand_buffer(buffer, size, current_char);
		*bit_count = 0;
		current_char = 0;
	}
}

void	signal_handler(int signum, siginfo_t *info, void *ucontext)
{
	static char		*msg_buffer = NULL;
	static int		bit_count = 0;
	static int		buffer_size = 0;

	(void)ucontext;
	if (g_current_client_pid == 0)
		g_current_client_pid = info->si_pid;
	else if (g_current_client_pid != info->si_pid)
		return ;
	process_character(signum, &msg_buffer, &bit_count, &buffer_size);
	if (kill(info->si_pid, SIGUSR1) == -1)
		handle_error("Warning: Failed to send acknowledgment\n", &msg_buffer);
	if (msg_buffer == NULL)
	{
		g_current_client_pid = 0;
		buffer_size = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("Server PID: %d\n", getpid());
	sigemptyset(&act.sa_mask);
	act.sa_sigaction = signal_handler;
	act.sa_flags = SA_SIGINFO | SA_RESTART;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
		handle_error("Error: Failed to set SIGUSR1 handler", NULL);
	if (sigaction(SIGUSR2, &act, NULL) == -1)
		handle_error("Error: Failed to set SIGUSR2 handler", NULL);
	while (1)
		pause();
	return (0);
}
