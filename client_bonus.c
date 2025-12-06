/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:12:18 by mesalman          #+#    #+#             */
/*   Updated: 2025/11/27 13:23:11 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static volatile sig_atomic_t	g_ack = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

static void	send_byte(pid_t pid, unsigned char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		g_ack = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_ack)
			pause();
		bit--;
	}
}

int	main(int ac, char **av)
{
	pid_t				pid;
	int					i;
	struct sigaction	sa;

	if (ac != 3)
		return (write(2, "Usage: ./client <pid> <msg>\n", 29), 1);
	pid = ft_atoi(av[1]);
	if (kill(pid, 0) == -1)
		return (write(2, "Invalid PID\n", 12), 1);
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ack_handler;
	sigaction(SIGUSR1, &sa, NULL);
	i = 0;
	while (av[2][i])
	{
		send_byte(pid, (unsigned char)av[2][i]);
		i++;
	}
	send_byte(pid, 0);
	write(1, "Message sent!\n", 14);
	return (0);
}
