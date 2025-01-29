/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:22 by icunha-t          #+#    #+#             */
/*   Updated: 2025/01/29 17:09:27 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk_bonus.h"

void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int	bit_pos;
	static int	i;
	
	(void)info;
	(void)context;
	if(signal == SIGUSR1)
		i |= (0x01 << bit_pos);
	bit_pos++;
	if(bit_pos == 8)
	{
		ft_printf("%c", i);
		bit_pos = 0;
		i = 0;
		kill(info->si_pid, SIGUSR2);
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;
	struct sigaction	sig;

	(void)av;
	if (ac != 1)
	{	
		ft_putstr_fd(RED"Error. Run with: ./server \n"RESET, 2);
		return (1);
	}
	pid = getpid();
	ft_printf(YELLOW"Process ID(PID): %d\n"RESET, pid);
	sig.sa_sigaction = signal_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	while (1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause();
	}
	return (0);
}
