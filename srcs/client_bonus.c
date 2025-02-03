/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:29 by icunha-t          #+#    #+#             */
/*   Updated: 2025/01/30 17:27:33 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk_bonus.h"

void	print_error(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit (1);
}

static void	sig_confirm(int signal)
{
	if (signal == SIGUSR1 || signal == SIGUSR2)
		ft_printf(YELLOW"Message received\n"RESET);
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
		pause();
		c >>= 1;
		bit_pos++;
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
	signal(SIGUSR1, sig_confirm);
	signal(SIGUSR2, sig_confirm);
	send_bits_to_server(pid, "Client: ");
	send_bits_to_server(pid, av[2]);
	null_bit = 0;
	while (null_bit < 8)
	{
		kill(pid, SIGUSR2);
		usleep(100);
		null_bit++;
	}
	return (0);
}
