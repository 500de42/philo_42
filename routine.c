/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:01:09 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/19 19:55:51 by kalvin           ###   ########.fr       */
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
		ft_usleep(100);
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
		if (p->i % 2 == 0)
		{
			
			pthread_mutex_lock(&p->left_fork);
			pthread_mutex_lock(p->right_fork);
			pthread_mutex_lock(&p->d->mutex_for_print);
			ft_printf("%d philo %d has taken left fork\n", get_time_programme(p->d), p->id_philo);
			ft_printf("%d philo %d has taken right fork\n", get_time_programme(p->d), p->id_philo);			
			pthread_mutex_unlock(&p->d->mutex_for_print);
		}
		else
		{
			
			pthread_mutex_lock(p->right_fork);
			pthread_mutex_lock(&p->left_fork);
			pthread_mutex_lock(&p->d->mutex_for_print);
			ft_printf("%d philo %d has taken right fork\n", get_time_programme(p->d), p->id_philo);
			ft_printf("%d philo %d has taken left fork\n", get_time_programme(p->d), p->id_philo);
			pthread_mutex_unlock(&p->d->mutex_for_print);
		}
		pthread_mutex_lock(&p->d->last_eat_mutex);
		*p->last_eat = get_current_time();
		pthread_mutex_unlock(&p->d->last_eat_mutex);
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("%ld philo %d mange\n", get_time_programme(p->d), p->id_philo);
		pthread_mutex_unlock(&p->d->mutex_for_print);
		pthread_create(&p->philo, NULL, verif_eat, (void *)p);
		pthread_mutex_unlock(&p->left_fork);
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("%ld philo %d dors\n",get_time_programme(p->d), p->id_philo);
		pthread_mutex_unlock(&p->d->mutex_for_print);
		pthread_create(&p->philo, NULL, verif_sleep, (void *)p);
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("%ld philo %d pense\n",get_time_programme(p->d), p->id_philo);
		pthread_mutex_unlock(&p->d->mutex_for_print);	
		nb_eat++;
	}
	return (NULL);
}

void	*verif_eat(void *random)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)random;
	data = philo->d;
	ft_usleep(philo->time_to_eat + 1);
	if (get_dead_time(data, philo))
	{
		pthread_mutex_lock(&data->mutex_for_print);
		ft_printf("the philo %d is dead\n",
			philo->id_philo);
		pthread_mutex_unlock(&data->mutex_for_print);
		philo->philo_dead = 1;
		exit(1);
		// fonction qui stop tout et clear
	}
	return (NULL);
}

void	*verif_sleep(void *random)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)random;
	data = philo->d;
	ft_usleep(philo->time_to_sleep + 1);
	if (get_dead_time(data, philo))
	{
		pthread_mutex_lock(&data->mutex_for_print);
		ft_printf("the philo %d is dead\n",
			philo->id_philo);
		pthread_mutex_unlock(&data->mutex_for_print);
		philo->philo_dead = 1;
		exit(1);
		// fonction qui stop tout et clear
	}
	return (NULL);
}
