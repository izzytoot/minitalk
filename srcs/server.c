/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:22 by icunha-t          #+#    #+#             */
/*   Updated: 2025/01/29 16:22:49 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"
#include <sys/time.h>
#include <stdio.h>

void	signal_handler(int signal)
{
	static int	bit_pos;
	static int	i;

	if(signal == SIGUSR1)
		i |= (0x01 << bit_pos);
	bit_pos++;
	if(bit_pos == 8)
	{
		ft_printf("%c", i);
		bit_pos = 0;
		i = 0;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;

	(void)av;
	if (ac != 1)
	{	
		ft_printf("Error. Run with: ./server \n");
		return (1);
	}
	pid = getpid();
	ft_printf("Process ID(PID): %d\n", pid);
	while (1)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		pause();
	}
	return (0);
}
