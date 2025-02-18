/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:01:58 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/18 21:41:45 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_philo **philo, t_data *data)
{
	int	i;

	i = -1;
	if (pthread_create(&data->philo_get, NULL, routine_thread,
		 (void *)philo) != 0)
	{
		ft_putstr_fd("error creation pthread_getteur\n", 2);
		// fonction qui clear tout
		return ;
	}	
	while (++i < data->nb_philo)
	{
		data->i = i;
		philo[i]->i = i;
		if (pthread_create(&philo[i]->philo, NULL, routine, (void *)philo[i]) != 0)
		{
			ft_putstr_fd("error creation pthread\n", 2);
			// fonction qui clear tout
			return ;
		}
	}
}

void	loop_for_wait_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (philo[i])
	{
		if (pthread_join(philo[i]->philo, NULL) != 0)
		{
			ft_putstr_fd("error pthread_join", 2);
			// fonction qui clean tout
		}
		i++;
	}
	if (pthread_join(data->philo_get, NULL) != 0)
	{
		ft_putstr_fd("error pthread_join philo get", 2);
		// fonction qui clean tout
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_time_programme(t_data *data)
{
	return ((get_current_time()) - data->starting_time);
}

int	get_dead_time(t_data *data, int i, t_philo **philo_list)
{
	size_t	is_dead;
	
	if (i < 0 || i >= data->nb_philo)
	{
    	pthread_mutex_lock(&data->mutex_for_print);
    	ft_printf("Index %d hors limites !\n", i);
    	pthread_mutex_unlock(&data->mutex_for_print);
    	return (0);
	}
	pthread_mutex_lock(&data->last_eat_mutex);
	is_dead = get_current_time() - philo_list[i]->last_eat;
	//pthread_mutex_lock(&data->mutex_for_print);
	// ft_printf("\n\ncurrent time %d\nphilo %d\ncalcul isdead %d\nlast eat %d\ntimetodead%d\n\n", 
	// get_current_time(),philo_list[i]->id_philo, is_dead, philo_list[i]->last_eat, data->time_to_dead);
	// ft_printf("\nnb %d isdead %d\n", philo_list[i]->id_philo,is_dead);
	//pthread_mutex_unlock(&data->mutex_for_print);
	pthread_mutex_unlock(&data->last_eat_mutex);
	if (is_dead >= (size_t)data->time_to_dead)
		return (1);
	return (0);
}
