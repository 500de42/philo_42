/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:46:19 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/10 16:28:06 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_before_loop(char **av, int i, int ac)
{
	if (((ac < 5) || (ac > 6)))
	{
		ft_putstr_fd("the number of arguments must be 4 or 5\n", 2);
		exit(1);
	}
	if (ft_atoll(av[i]) > INT_MAX || ft_atoll(av[i]) < INT_MIN)
	{
		ft_putstr_fd("INT_MIN or INT_MAX exceeded\n", 2);
		exit(1);
	}
	if (ft_atoll(av[i]) < 0)
	{
		ft_putstr_fd("negative number detected\n", 2);
		exit(1);
	}
	if (ft_atoi(av[i]) == 0)
	{
		ft_putstr_fd("0 is not valid argument\n", 2);
		exit(1);
	}
}

void	check_arg(char **av, int ac)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		check_before_loop(av, i, ac);
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				ft_putstr_fd("caractere non numerique\n", 2);
				exit(1);
			}
		}
		if (av[i][0] - '0' == 0)
		{
			ft_putstr_fd("argument strating with 0 is not valid\n", 2);
			exit(1);
		}
	}
}
