/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:01:58 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/11 17:35:50 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_philo **philo, t_data *data)
{
	int	i;

	i = -1;
	data->starting_time = get_current_time();
	while (++i < data->nb_philo)
	{
		data->i = i;
		philo[i]->i = i;
		if (pthread_create(&philo[i]->philo, NULL, routine,
				(void *)philo[i]) != 0)
		{
			ft_putstr_fd("error creation pthread\n", 2);
			return ;
		}
	}
}

void	destroy_data(t_data *data)
{
	pthread_mutex_destroy(&data->mutex_finish);
	pthread_mutex_destroy(&data->mutex_finish_eat);
	pthread_mutex_destroy(&data->mutex_for_print);
	pthread_mutex_destroy(&data->mutex_for_count_meal);
	pthread_mutex_destroy(&data->mutex_for_dead);
	pthread_mutex_destroy(&data->last_eat_mutex);
}

void	loop_for_wait_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philo[i]->philo, NULL))
			ft_putstr_fd("error pthread_join", 2);
		if (data->nb_philo > 1)
			if (pthread_join(philo[i]->thread_eat, NULL))
				ft_putstr_fd("error pthread_join2", 2);
		i++;
	}
	destroy_data(data);
	i = -1;
	while (++i < data->nb_philo)
	{
		free(philo[i]->last_eat);
		pthread_mutex_destroy(&philo[i]->left_fork);
		free(philo[i]);
	}
	free(philo[i]);
	free(data);
	free(philo);
	return ;
}

size_t	get_time_programme(t_data *data)
{
	return ((get_current_time()) - data->starting_time);
}

int	get_dead_time(t_data *data, t_philo *philo_list)
{
	size_t	is_dead;

	pthread_mutex_lock(&data->last_eat_mutex);
	is_dead = get_current_time() - *philo_list->last_eat;
	pthread_mutex_unlock(&data->last_eat_mutex);
	pthread_mutex_lock(&data->mutex_for_time);
	if (is_dead >= (size_t)data->time_to_dead)
		return (1);
	return (0);
}
