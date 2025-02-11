/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:45:38 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/11 21:37:38 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_val_philo(t_philo **tmp, char **av, int i, int ac)
{
	(*tmp)->id_philo = i + 1;
	if (ac == 6)
		(*tmp)->finish_eat = ft_atoi(av[5]);
	else
		(*tmp)->finish_eat = 0;
	(*tmp)->nb_eat = 0;
	(*tmp)->ms_eat = 0;
	(*tmp)->time_to_dead = 0;
	(*tmp)->time_to_eat = 0;
	(*tmp)->time_to_sleep = 0;
	pthread_mutex_init(&(*tmp)->left_fork, NULL);
	// (*tmp)->right_fork = NULL;
	// (*tmp)->philo = NULL;
}

void	init_philo(char **av, int ac, t_philo ***philo_list, t_data *data)
{
	int		i;

	i = -1;
	*philo_list = malloc(sizeof(t_philo *) * (data->nb_philo + 1));
	if (!(*philo_list))
		return ;
	while (++i < data->nb_philo)
	{
		(*philo_list)[i] = malloc(sizeof(t_philo));
		if (!(*philo_list)[i])
		{
			erreur_init_philo(*philo_list, i);
			ft_putstr_fd("error initialisation", 2);
			exit(1);
		}
		init_val_philo(philo_list[i], av, i, ac);
	}
	(*philo_list)[i] = NULL;
}

int	init_data(t_data **data, size_t time_, char **av)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (1);
	(*data)->starting_time = time_;
	(*data)->nb_philo = ft_atoi(av[1]);
	pthread_mutex_init(&(*data)->mutex_for_print, NULL);
	return (0);
}
