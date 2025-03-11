/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:15:06 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/11 17:35:57 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	split_dead_(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutex_finish_eat);
	if (philo->finish_eat)
	{
		pthread_mutex_unlock(&data->mutex_finish_eat);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_finish_eat);
	return (0);
}

int	dead_split(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutex_finish_eat);
	if (philo->finish_eat)
	{
		pthread_mutex_unlock(&data->mutex_finish_eat);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_finish_eat);
	pthread_mutex_lock(&data->mutex_for_dead);
	if (data->philo_dead)
	{
		pthread_mutex_unlock(&data->mutex_for_dead);
		return (1);
	}
	pthread_mutex_lock(&data->mutex_finish_eat);
	if (philo->finish_eat)
	{
		pthread_mutex_unlock(&data->mutex_for_dead);
		pthread_mutex_unlock(&data->mutex_finish_eat);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_finish_eat);
	data->philo_dead = true;
	pthread_mutex_unlock(&data->mutex_for_dead);
	return (0);
}

int	split_dead2(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->mutex_finish);
	if (data->finish)
	{
		pthread_mutex_unlock(&data->mutex_finish);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_finish);
	pthread_mutex_lock(&data->mutex_for_print);
	ft_printf("%d the philo %d died\n", get_current_time()
		- data->starting_time, philo->id_philo);
	pthread_mutex_unlock(&data->mutex_for_print);
	return (0);
}

void	*verif_dead(void *random)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)random;
	data = philo->d;
	while (1)
	{
		if (split_dead_(philo, data))
			return (NULL);
		pthread_mutex_lock(&data->last_eat_mutex);
		if ((get_current_time()
				- *philo->last_eat) >= (size_t)philo->time_before_dead)
		{
			pthread_mutex_unlock(&data->last_eat_mutex);
			if (dead_split(philo, data) || split_dead2(philo, data))
				return (NULL);
			return (NULL);
		}
		pthread_mutex_unlock(&data->last_eat_mutex);
		usleep(philo->time_before_dead * 100);
	}
	return (NULL);
}
