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

#include "minitalk_bonus.h"

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	ch;
	static int				bit;

	(void)context;
	ch <<= 1;
	if (sig == SIGUSR1)
		ch |= 1;
	bit++;
	if (bit == 8)
	{
		if (ch == 0)
			write(1, "\n", 1);
		else
			write(1, &ch, 1);
		ch = 0;
		bit = 0;
	}
	if (info && info->si_pid != 0)
		kill(info->si_pid, SIGUSR1);
}

static void	setup_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(2, "Error: sigaction failed\n", 24);
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		write(2, "Error: sigaction failed\n", 24);
		exit(EXIT_FAILURE);
	}
}

int	main(void)
{
	write(1, "Server PID = ", 13);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	setup_signals();
	while (1)
		pause();
	return (0);
}
