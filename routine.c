/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:01:09 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/13 21:38:43 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *random)
{
	t_data	*d;
	t_philo	**p;
	
	d = (t_data *)random;
	p = d->philo_list;
	while (1)
	{
		if (p[d->i]->philo_dead)
		{
			ft_printf("philo %d est mort", p[]->id_philo);
			// fonction qui clear tout
		}
		if (d->i % 2 == 0)
			usleep(d->time_to_eat / 10);
		pthread_mutex_lock(&d->mutex_for_print);
		ft_printf("philo %d mange", p[d->i]->id_philo);
		pthread_mutex_unlock(&d->mutex_for_print);
		p[d->i]->last_eat = get_current_time();
		pthread_mutex_lock(&p[d->i]->left_fork);
		pthread_mutex_lock(p[d->i]->right_fork);
		usleep(p[d->i]->time_to_eat);
		pthread_mutex_unlock(&p[d->i]->left_fork);
		pthread_mutex_unlock(p[d->i]->right_fork);
		pthread_mutex_lock(&d->mutex_for_print);
		ft_printf("philo %d dors", p[d->i]->id_philo);
		pthread_mutex_unlock(&d->mutex_for_print);
		usleep(p[d->i]->time_to_sleep);
		pthread_mutex_lock(&d->mutex_for_print);
		ft_printf("philo %d pense", p[d->i]->id_philo);
		pthread_mutex_unlock(&d->mutex_for_print);
	}
	return (NULL);
}

void	*routine_thread(void *random)
{
	int		i;
	t_data	*data;

	data = (t_data *)random;
	i = 0;
	while (1)
	{
		while (++i < data->nb_philo)
		{
			if (get_dead_time(data, i))
			{
				pthread_mutex_lock(&data->mutex_for_print);
				ft_printf("the philo %d is dead",
					data->philo_list[i]->id_philo);
				pthread_mutex_unlock(&data->mutex_for_print);
				data->philo_list[i]->philo_dead = 1;
				// fonction qui stop tout et clear
			}
		}
		i = -1;
	}
	return (NULL);
}
