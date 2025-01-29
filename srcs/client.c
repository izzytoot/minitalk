/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:29 by icunha-t          #+#    #+#             */
/*   Updated: 2025/01/29 18:30:05 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	send_bits_to_server(int pid, char letter)
{
	int	bit_pos;

	bit_pos = 0;
	while (bit_pos < 8)
	{
		if ((letter & (0x01 << bit_pos)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		sleep(500);
		bit_pos++;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	char	*message;

	if (ac != 3)
	{
		ft_putstr_fd(RED"Error. "RESET, 2);
		ft_putstr_fd(RED "Run with: ./client <PID> <message string>\n"RESET, 2);
		return (1);
	}
	else
	{
		pid = ft_atoi(av[1]);
		message = av[2];
		while (*message)
		{
			send_bits_to_server(pid, *message);
			message++;
		}
		send_bits_to_server(pid, '\n');
	}
	return (0);
}
