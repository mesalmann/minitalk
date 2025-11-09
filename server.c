/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:13:32 by mesalman          #+#    #+#             */
/*   Updated: 2025/11/09 17:08:58 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_bit(int sig)
{
	static unsigned char	c = 0;
	static int				bit = 0;

	if (sig == SIGUSR1)
		c |= 1 << (7 - bit);
	bit++;
	if (bit == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &print_bit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(1, "ERROR\n", 1);
		exit(EXIT_FAILURE);
	}	
}

void	print_pid(void)
{
	pid_t	pid;

	pid = getpid();
	write(1, "Server PID =", 12);
	ft_putnbr(pid);
	write(1, "\n", 1);
}

int	main(void)
{
	print_pid();
	setup_signals();
	while (1)
		pause();
	return (0);
}
