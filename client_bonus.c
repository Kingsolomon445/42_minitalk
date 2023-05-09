/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:54:23 by ofadahun          #+#    #+#             */
/*   Updated: 2023/05/09 11:42:55 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	sig_handler(int sig_num)
{
	if (sig_num == SIGUSR1)
	{
		ft_printf("Message received\n");
		exit(EXIT_SUCCESS);
	}
}

void	set_handler(void)
{
	struct sigaction	act;
	sigset_t			mask;

	sigemptyset(&mask);
	act.sa_flags = 0;
	act.sa_handler = sig_handler;
	act.sa_mask = mask;
	sigaction(SIGUSR1, &act, NULL);
}

void	eval_char_to_bin(int spid, unsigned char ch)
{
	int	bit;

	bit = 0;
	while (bit <= 7)
	{
		if ((ch >> bit) & 1)
		{
			if (kill(spid, SIGUSR1) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (kill(spid, SIGUSR2) == -1)
				exit(EXIT_FAILURE);
		}
		bit++;
		usleep(100);
	}
}

int	main(int argc, char *argv[])
{
	pid_t	spid;
	int		i;

	i = 0;
	if (argc != 3)
	{
		ft_printf("Usage: %s [server PID] [string]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	spid = ft_atoi(argv[1]);
	if (spid == 0)
	{
		ft_printf("Enter valid server ID\n");
		exit(EXIT_FAILURE);
	}
	set_handler();
	while (argv[2][i])
	{
		eval_char_to_bin(spid, argv[2][i]);
		i++;
	}
	eval_char_to_bin(spid, '\0');
	return (0);
}
