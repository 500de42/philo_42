/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:15:06 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/23 22:20:27 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = (long int)get_current_time();
	while (((long int)get_current_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

void	*verif_dead(void *random)
{
	t_philo	*philo;
	t_data	*data;
	size_t	last_eat;

	philo = (t_philo *)random;
	data = philo->d;
	pthread_mutex_lock(&data->last_eat_mutex);
	last_eat = *philo->last_eat;
	pthread_mutex_unlock(&data->last_eat_mutex);
	while ((get_current_time() - last_eat) < (size_t)philo->time_before_dead)
		ft_usleep(100);
	if ((get_current_time() - last_eat) >= (size_t)philo->time_before_dead)
	{
		pthread_mutex_lock(&data->mutex_for_dead);
		if (data->philo_dead)
		{
			pthread_mutex_unlock(&data->mutex_for_dead);
			return (NULL);
		}
		data->philo_dead = true;
		pthread_mutex_unlock(&data->mutex_for_dead);
		pthread_mutex_lock(&data->mutex_for_print);
		ft_printf("%d the philo %d died", get_time_programme(data), philo->id_philo);
		pthread_mutex_unlock(&data->mutex_for_print);
		return (NULL);
	}
	return (NULL);
}

int	safe_print(char *str, t_philo *ph)
{
	size_t	time;
	t_data	*data;

	data = ph->d;
	pthread_mutex_lock(&data->mutex_for_dead);
	if (data->philo_dead == true)
	{
		pthread_mutex_unlock(&data->mutex_for_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_for_dead);
	time = get_time_programme(data);
	pthread_mutex_lock(&data->mutex_for_print);
	ft_printf("%d the philo %d %s\n", time, ph->id_philo, str);
	pthread_mutex_unlock(&data->mutex_for_print);
	return (0);
}

void	let_go_forks(t_philo *p)
{
	if (p->id_philo % 2 == 0)
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(&p->left_fork);
	}
	else
	{
		pthread_mutex_unlock(&p->left_fork);
		pthread_mutex_unlock(p->right_fork);
	}
}

// pthread_mutex_lock(&data->mutex_for_print);
// ft_printf("DEBUG: last_eat address = %p, value = %d\n", philo->last_eat,
//	*philo->last_eat);
// pthread_mutex_unlock(&data->mutex_for_print);
// pthread_mutex_lock(&data->mutex_for_print);
// ft_printf("DEBUG: current_time = %d, last_eat = %d, diff = %d,
//	time_before_dead = %d\n",
// get_current_time(), *philo->last_eat, get_current_time() - *philo->last_eat,
//	philo->time_before_dead);
// pthread_mutex_unlock(&data->mutex_for_print);
