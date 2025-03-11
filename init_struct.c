/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:45:38 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/11 16:45:04 by kcharbon         ###   ########.fr       */
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
	tmp->nb_philo = ft_atoi(av[1]);
	tmp->count_eat = 0;
	tmp->time_before_dead = ft_atoi(av[2]);
	tmp->time_to_eat = ft_atoi(av[3]);
	tmp->time_to_sleep = ft_atoi(av[4]);
	tmp->i = i;
	tmp->philo_dead = 0;
	tmp->finish_eat = 0;
	pthread_mutex_init(&tmp->left_fork, NULL);
}

void	in(char **av, t_philo ***philo_list, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (ft_atoi(av[1]) > 1)
		{
			if (i == 0)
			{
				(*philo_list)[i]->right_fork = &(*philo_list)[ft_atoi(av[1])
					- 1]->left_fork;
				(*philo_list)[i]->id_fork = (*philo_list)[ft_atoi(av[1])
					- 1]->id_philo;
			}
			else
			{
				(*philo_list)[i]->right_fork = &(*philo_list)[i - 1]->left_fork;
				(*philo_list)[i]->id_fork = (*philo_list)[i - 1]->id_philo;
			}
		}
	}
}

void	free_(t_philo ***philo_list, int a, t_data *data, bool f)
{
	pthread_mutex_destroy(&data->mutex_finish);
	pthread_mutex_destroy(&data->mutex_finish_eat);
	pthread_mutex_destroy(&data->mutex_for_print);
	pthread_mutex_destroy(&data->mutex_for_count_meal);
	pthread_mutex_destroy(&data->mutex_for_dead);
	pthread_mutex_destroy(&data->last_eat_mutex);
	free(data);
	if (f)
	{
		ft_putstr_fd("error initialisation", 2);
		erreur_init_philo(*philo_list, a);
	}
	exit(1);
}

void	init_philo(char **av, int ac, t_philo ***philo_list, t_data *data)
{
	int	i;

	i = -1;
	*philo_list = malloc(sizeof(t_philo *) * (ft_atoi(av[1]) + 1));
	if (!*philo_list)
		free_(philo_list, 0, data, false);
	while (++i < data->nb_philo)
	{
		(*philo_list)[i] = malloc(sizeof(t_philo));
		if (!(*philo_list)[i])
			free_(philo_list, i, data, true);
		(*philo_list)[i]->d = data;
		(*philo_list)[i]->last_eat = malloc(sizeof(size_t));
		if (!((*philo_list)[i]->last_eat))
			free_(philo_list, i, data, true);
		init_val_philo((*philo_list)[i], av, i, ac);
	}
	(*philo_list)[i] = NULL;
	in(av, philo_list, data);
}

int	init_data(t_data **data, char **av)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
	{
		ft_printf("erreur alloc data");
		return (1);
	}
	(*data)->starting_time = 0;
	(*data)->count_meal = 0;
	(*data)->finish = 0;
	(*data)->nb_philo = ft_atoi(av[1]);
	(*data)->time_to_dead = ft_atoi(av[2]);
	(*data)->time_to_sleep = ft_atoi(av[4]);
	(*data)->time_to_eat = ft_atoi(av[3]);
	(*data)->philo_dead = false;
	pthread_mutex_init(&(*data)->mutex_finish_eat, NULL);
	pthread_mutex_init(&(*data)->mutex_finish, NULL);
	pthread_mutex_init(&(*data)->mutex_for_time, NULL);
	pthread_mutex_init(&(*data)->mutex_for_print, NULL);
	pthread_mutex_init(&(*data)->last_eat_mutex, NULL);
	pthread_mutex_init(&(*data)->mutex_for_count_meal, NULL);
	pthread_mutex_init(&(*data)->mutex_for_dead, NULL);
	return (0);
}
