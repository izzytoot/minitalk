/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:29 by icunha-t          #+#    #+#             */
/*   Updated: 2025/01/30 17:30:38 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	print_error(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit (1);
}

void	bit_converter(int pid, char c)
{
	int	bit_pos;

	bit_pos = 0;
	while (bit_pos < 8)
	{
		if (c & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		c >>= 1;
		bit_pos++;
		usleep(500);
	}
}

void	send_bits_to_server(int pid, char *message)
{
	int	i;

	i = 0;
	while (message[i])
		bit_converter(pid, message[i++]);
	bit_converter(pid, '\0');
}

int	main(int ac, char **av)
{
	pid_t	pid;
	int		null_bit;

	if (ac != 3)
		print_error(RED"Error. Run with: ./client <PID> <message>\n"RESET);
	pid = ft_atoi(av[1]);
	send_bits_to_server(pid, "Client: ");
	send_bits_to_server(pid, av[2]);
	null_bit = 0;
	while (null_bit < 8)
	{
		kill(pid, SIGUSR2);
		usleep(300);
		null_bit++;
	}
	return (0);
}
