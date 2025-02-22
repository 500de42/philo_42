/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:15:06 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/22 23:10:25 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = get_current_time();
	while (((long int)get_current_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

// void	*verif_dead(void *random)
// {
// 	t_philo	*philo;
// 	t_data	*data;

// 	philo = (t_philo *)random;
// 	data = philo->d;
// 	ft_usleep(philo->time_before_dead + 1);
// 	if (get_dead_time(data, philo))
// 	{
// 		pthread_mutex_lock(&data->mutex_for_print);
// 		ft_printf("%d the philo %d died\n",
// 			get_time_programme(data), philo->id_philo);
// 		pthread_mutex_unlock(&data->mutex_for_print);
// 		philo->philo_dead = 1;
// 		exit(1);
// 		// fonction qui stop tout et clear
// 	}
// 	return (NULL);
// }

void	*	verif_dead(void *random)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)random;
	data = philo->d;
	pthread_mutex_lock(&data->last_eat_mutex);
	while ((get_current_time() - *philo->last_eat) < (size_t)philo->time_before_dead)
	{
		ft_usleep(5);
		// pthread_mutex_lock(&data->mutex_for_print);
		// ft_printf("last eat %d\n", (get_current_time() - *philo->last_eat));
		// pthread_mutex_unlock(&data->mutex_for_print);
	}
	// pthread_mutex_lock(&data->mutex_for_print);
	// ft_printf("last eat %d philo %d\n", (get_current_time() - *philo->last_eat), philo->id_philo);
	// pthread_mutex_unlock(&data->mutex_for_print);
	if ((get_current_time() - *philo->last_eat) >= (size_t)philo->time_before_dead)
	{
		pthread_mutex_lock(&data->mutex_for_print);
		ft_printf("%d the philo %d died\n",
			get_time_programme(data), philo->id_philo);
		pthread_mutex_unlock(&data->mutex_for_print);
		philo->philo_dead = 1;
		pthread_mutex_unlock(&data->last_eat_mutex);
		if (philo->id_philo % 2 == 0)
		{	
			pthread_mutex_unlock(philo->right_fork);
			pthread_mutex_unlock(&philo->left_fork);
		}
		else
		{
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
		}
		pthread_mutex_lock(&data->mutex_for_dead);
		data->philo_dead = true;
		pthread_mutex_unlock(&data->mutex_for_dead);
		exit(1);
		// fonction qui stop tout et clear
	}
	pthread_mutex_unlock(&data->last_eat_mutex);
	return (NULL);
}

int    safe_print(char str, t_philo	*ph)
{
    long int    time;
    t_data        *data;

    data = ph->d;
    pthread_mutex_lock(&data->mutex_for_print);
    if (is_dead(data->philo_dead))
    {
        pthread_mutex_unlock(&data->mutex_for_print);
        return (1);
    }
    time = (long int)get_time_programme(data);
    ft_printf("%ld the philo %d %s", time, ph->id_philo, str);
    pthread_mutex_unlock(&data->mutex_for_print);
    return (0);
}

// pthread_mutex_lock(&data->mutex_for_print);
// ft_printf("DEBUG: last_eat address = %p, value = %d\n", philo->last_eat, *philo->last_eat);
// pthread_mutex_unlock(&data->mutex_for_print);
// pthread_mutex_lock(&data->mutex_for_print);
// ft_printf("DEBUG: current_time = %d, last_eat = %d, diff = %d, time_before_dead = %d\n",
// get_current_time(), *philo->last_eat, get_current_time() - *philo->last_eat, philo->time_before_dead);
// pthread_mutex_unlock(&data->mutex_for_print);
