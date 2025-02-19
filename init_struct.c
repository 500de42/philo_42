/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:45:38 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/19 20:00:28 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_val_philo(t_philo *tmp, char **av, int i, int ac)
{	
	tmp->id_philo = i + 1;
	if (ac == 6)
		tmp->nb_eat = ft_atoi(av[5]);
	else
		tmp->nb_eat = 0;
	tmp->count_eat = 0;
	tmp->ms_eat = 0;
	tmp->time_before_dead = ft_atoi(av[2]);
	tmp->time_to_eat = ft_atoi(av[3]);
	tmp->time_to_sleep = ft_atoi(av[4]);
	tmp->i = i;
	tmp->philo_dead = 0;
	pthread_mutex_init(&tmp->left_fork, NULL);
}

void	init_philo(char **av, int ac, t_philo ***philo_list, t_data *data)
{
	int	i;

	i = -1;
	*philo_list = malloc(sizeof(t_philo *) * (ft_atoi(av[1]) + 1));
	if (!*philo_list)
	{
		// fonction qui free tout
		return ;
	}
	while (++i < data->nb_philo)
	{
		(*philo_list)[i] = malloc(sizeof(t_philo));
		if (!(*philo_list)[i])
		{
			erreur_init_philo(*philo_list, i);
			ft_putstr_fd("error initialisation", 2);
			exit(1);
		}
		(*philo_list)[i]->d = data;
		(*philo_list)[i]->last_eat = malloc(sizeof (size_t));
		if (!((*philo_list)[i]->last_eat))
		{
			ft_printf("erreur malloc variable last_eat");
			exit(1);
		}
		*(*philo_list)[i]->last_eat = data->starting_time;
		// ft_printf("\n\n%d\n\n%d\n\n", data->starting_time, (*philo_list)[i]->last_eat);
		init_val_philo((*philo_list)[i], av, i, ac);
	}
	(*philo_list)[i] = NULL;
	i = -1;
	while ((*philo_list)[++i])
	{
		if (ft_atoi(av[1]) > 1)
		{
			if (i == 0)
				(*philo_list)[i]->right_fork = &(*philo_list)[ft_atoi(av[1]) - 1]->left_fork;
			else
				(*philo_list)[i]->right_fork = &(*philo_list)[i - 1]->left_fork;
		}
	}
}

int	init_data(t_data **data, size_t time_, char **av)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (1);
	(*data)->starting_time = time_;
	(*data)->nb_philo = ft_atoi(av[1]);
	(*data)->time_to_dead = ft_atoi(av[2]);
	(*data)->time_to_sleep = ft_atoi(av[4]);
	(*data)->time_to_eat = ft_atoi(av[3]);
	pthread_mutex_init(&(*data)->mutex_for_print, NULL);
	pthread_mutex_init(&(*data)->last_eat_mutex, NULL);
	return (0);
}
