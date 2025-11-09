/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mesalman <mesalman@student.42istanbul.com  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:45:06 by mesalman          #+#    #+#             */
/*   Updated: 2025/11/09 17:02:34 by mesalman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	send_bit(pid_t pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> (7 - bit)) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit++;
		usleep(1000);
	}
}

void	send_cpid(pid_t pid, int cpid)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if ((cpid >> (31 - i)) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(1000);
	}
}

void	wait_for_ack(void)
{
	pause();
}

void	ack_handler(int sig)
{
	(void)sig;
}

int	main(int ac, char **av)
{
	char	*str;
	int		i;
	int		cpid;
	pid_t	pid;

	if (ac != 3)
		return (0);
	pid = ft_atoi(av[1]);
	str = av[2];
	i = 0;
	cpid = getpid();
	send_cpid(pid, cpid);
	signal(SIGUSR1, ack_handler);
	while (str[i])
	{
		send_bit (pid, str[i]);
		wait_for_ack();
		i++;
	}
	send_bit(pid, '\0');
	wait_for_ack();
	return (0);
}
