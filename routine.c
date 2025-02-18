/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:01:09 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/18 21:37:22 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *random)
{
	t_philo	*p;
	int nb_eat;

	p = (t_philo *)random;
	nb_eat = 0;
	if (p->i % 2 == 0)
		usleep((p->time_to_eat / 10) * 1000);
	while (1)
	{		
		if (p->nb_eat > 0)
			if (nb_eat == p->nb_eat)
				{		
					pthread_mutex_lock(&p->d->mutex_for_print);
					ft_printf("simulation fini\n");
					pthread_mutex_unlock(&p->d->mutex_for_print);
					exit(0);
				}
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("philo %d mange\n", p->id_philo);
		pthread_mutex_unlock(&p->d->mutex_for_print);
		pthread_mutex_lock(&p->left_fork);
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(&p->d->last_eat_mutex);
		p->last_eat = get_current_time();
		pthread_mutex_unlock(&p->d->last_eat_mutex);
		usleep(p->time_to_eat * 1000);
		pthread_mutex_unlock(&p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("philo %d dors\n", p->id_philo);
		pthread_mutex_unlock(&p->d->mutex_for_print);
		usleep(p->time_to_sleep * 1000);
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("philo %d pense\n", p->id_philo);
		pthread_mutex_unlock(&p->d->mutex_for_print);
		if (p->time_to_eat > p->time_to_sleep)
			usleep((p->time_to_eat - p->time_to_sleep) * 1000);
		else
			usleep((p->time_to_sleep - p->time_to_eat) * 1000);		
		nb_eat++;
	}
	return (NULL);
}

void	*routine_thread(void *random)
{
	int		i;
	t_philo	**philo_list;
	t_data	*data;

	philo_list = (t_philo **)random;
	data = philo_list[0]->d;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{	
			// pthread_mutex_lock(&philo_list[i]->d->mutex_for_print);
			// ft_printf("nb philo%d\n%d", philo_list[i]->d->nb_philo, i);
			// pthread_mutex_unlock(&philo_list[i]->d->mutex_for_print);
			if (get_dead_time(data, i, philo_list))
			{
				pthread_mutex_lock(&data->mutex_for_print);
				ft_printf("the philo %d is dead\n",
					philo_list[i]->id_philo);
				pthread_mutex_unlock(&data->mutex_for_print);
				philo_list[i]->philo_dead = 1;
				// exit(1);
				// fonction qui stop tout et clear
			}
			i++;
		}
		
	}
	return (NULL);
}
