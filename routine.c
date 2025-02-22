/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:01:09 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/22 23:48:17 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	only_one_philo(t_philo *p)
{
	if (p->d->nb_philo == 1)
	{
		pthread_mutex_lock(&p->left_fork);
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("%d philo %d has taken left fork\n", get_time_programme(p->d), p->id_philo);		
		pthread_mutex_unlock(&p->d->mutex_for_print);
		ft_usleep(p->time_before_dead + 1);
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("%d philo %d is dead\n", get_time_programme(p->d), p->id_philo);
		pthread_mutex_unlock(&p->d->mutex_for_print);
		return (1);
	}
	return (0);
}

void	take_fork(t_philo *p)
{
	pthread_mutex_lock(&p->d->mutex_for_dead);
	if (!p->d->philo_dead)
	{
		pthread_mutex_unlock(&p->d->mutex_for_dead);
		if ((p->id_philo % 2) == 0)
		{
			pthread_mutex_lock(&p->left_fork);
			pthread_mutex_lock(p->right_fork);
			safe_print("has taken left fork", p);
			safe_print("has taken right fork", p);
		}
		else
		{
			pthread_mutex_lock(p->right_fork);
			pthread_mutex_lock(&p->left_fork);
			safe_print("has taken right fork", p);
			safe_print("has taken left fork", p);
		}
	}
}

int	check_meal(t_philo *p, int nb_eat, t_data *data)
{
	if (p->nb_eat > 0)
	{
		pthread_mutex_lock(&p->d->mutex_for_count_meal);
		if (nb_eat == p->nb_eat)
			data->count_meal++;
		if(data->count_meal == p->nb_eat)
		{
			pthread_mutex_lock(&data->mutex_for_dead);
			if (!data->philo_dead)
			{
				pthread_mutex_lock(&p->d->mutex_for_print);
				ft_printf("simulation fini\n");
				pthread_mutex_unlock(&p->d->mutex_for_print);
			}
			
			return (1);
		}
		pthread_mutex_unlock(&p->d->mutex_for_count_meal);
	}
	return (0);
}

void	routine_philo(t_philo *p)
{
	take_fork(p);
	pthread_mutex_lock(&p->d->last_eat_mutex);
	*p->last_eat = get_current_time();
	pthread_mutex_unlock(&p->d->last_eat_mutex);
	pthread_create(&p->philo, NULL, verif_dead, (void *)p);
	if (!safe_print("is eating", p))
		ft_usleep(p->time_to_eat);
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
	pthread_create(&p->philo, NULL, verif_dead, (void *)p);
	if (!safe_print("is sleeping", p))
		ft_usleep(p->time_to_sleep + 1);
	safe_print("is thinking", p);
}

void	*routine(void *random)
{
	t_philo	*p;
	int nb_eat;

	nb_eat = 0;
	p = (t_philo *)random;
	*p->last_eat = get_current_time();
	if ((p->id_philo % 2) == 0)
		ft_usleep(p->time_before_dead  / 10);
	if (only_one_philo(p))
		return (NULL);
	while (1)
	{		
		if (check_meal(p, nb_eat, p->d))
			return (NULL);
		routine_philo(p);
		nb_eat++;
	}
	return (NULL);
}
