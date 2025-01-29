/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:29 by icunha-t          #+#    #+#             */
/*   Updated: 2025/01/29 17:04:20 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk_bonus.h"

static void	sig_confirm(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("Message received\n");
	else
		ft_printf("Message received\n"); 
}

void send_bits_to_server(int pid, char letter)
{
	int	bit_pos;

	bit_pos = 0;
	while (bit_pos < 8) // size of 1 char
	{
		if ((letter & (0x01 << bit_pos)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit_pos++;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	char	*message;
	int	i;
	
	if(ac != 3) // program, pid, message
	{	
		ft_putstr_fd(RED"Error. Run with: ./client <PID> <message string>\n"RESET, 2);
		return (1);
	}
	else
	{
		pid = ft_atoi(av[1]);
		message = av[2];
		i = 0;
		while (message[i])
		{
			signal(SIGUSR1, sig_confirm);
			signal(SIGUSR2, sig_confirm);
			send_bits_to_server(pid, *message);
			i++;
		}
		send_bits_to_server(pid, '\n');
	}
	return (0);
}
