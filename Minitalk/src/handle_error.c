/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:48:04 by rkhakimu          #+#    #+#             */
/*   Updated: 2024/10/28 18:12:09 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	handle_error(const char *error_message)
{
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	exit(1);
}
