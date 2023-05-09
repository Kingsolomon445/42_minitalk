/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofadahun <ofadahun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:54:23 by ofadahun          #+#    #+#             */
/*   Updated: 2023/05/09 11:41:59 by ofadahun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	eval_char_to_bin(int spid, unsigned char ch)
{
	int	bit;

	bit = 0;
	while (bit <= 7)
	{
		if ((ch >> bit) & 1)
		{
			if (kill(spid, SIGUSR1) == -1)
			{
				ft_printf("Error\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (kill(spid, SIGUSR2) == -1)
			{
				ft_printf("Error\n");
				exit(EXIT_FAILURE);
			}
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
		ft_printf("Usage: %s [server_pid] [string]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	spid = ft_atoi(argv[1]);
	if (spid < 1)
	{
		ft_printf("Enter valid server id\n");
		exit(EXIT_FAILURE);
	}
	while (argv[2][i])
	{
		eval_char_to_bin(spid, argv[2][i]);
		i++;
	}
	return (0);
}
