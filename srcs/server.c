/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icunha-t <icunha-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:16:22 by icunha-t          #+#    #+#             */
/*   Updated: 2025/01/30 17:27:52 by icunha-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	print_error(char *error_message)
{
	ft_putstr_fd(error_message, 2);
	exit (1);
}

void	char_handler(char **message, char c)
{
	char	temp[2];
	char	*new_str;

	temp[0] = c;
	temp[1] = '\0';
	if (!*message)
		*message = ft_strdup(temp);
	else if (c == 0)
	{
		ft_printf("%s\n", *message);
		free(*message);
		*message = NULL;
	}
	else
	{
		new_str = ft_strjoin(*message, temp);
		free(*message);
		*message = ft_strdup(new_str);
		free(new_str);
	}
}

void	signal_handler(int signal)
{
	static int	bit_pos;
	static int	c;
	static char	*message;

	if (signal == SIGUSR1)
		c = c | (1 << bit_pos);
	bit_pos++;
	if (bit_pos == 8)
	{
		char_handler(&message, c);
		bit_pos = 0;
		c = 0;
	}
}

int	main(int ac, char **av)
{
	pid_t	pid;

	(void)av;
	if (ac != 1)
		print_error(RED"Error. Run with: ./server\n"RESET);
	pid = getpid();
	if (pid == -1)
		print_error(RED"Invalid PID.\n"RESET);
	ft_printf(YELLOW"Process ID(PID): %d\n"RESET, pid);
	while (1)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		pause();
	}
	return (0);
}
