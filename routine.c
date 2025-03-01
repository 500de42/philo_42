/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalvin <kalvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:01:09 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/01 22:07:18 by kalvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	only_one_philo(t_philo *p)
{
	if (p->d->nb_philo == 1)
	{
		pthread_mutex_lock(&p->left_fork);
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("%d philo %d has taken left fork\n", get_time_programme(p->d),
			p->id_philo);
		pthread_mutex_unlock(&p->d->mutex_for_print);
		usleep(p->time_before_dead * 1000);
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("%d philo %d died\n", get_time_programme(p->d),
			p->id_philo);
		pthread_mutex_unlock(&p->d->mutex_for_print);
		pthread_mutex_unlock(&p->left_fork);
		return (1);
	}
	return (0);
}

int	take_fork(t_philo *p)
{
	pthread_mutex_lock(&p->d->mutex_for_dead);
	if (p->d->philo_dead)
	{
		pthread_mutex_unlock(&p->d->mutex_for_dead);
		return (1);
	}
	pthread_mutex_unlock(&p->d->mutex_for_dead);
	if (p->id_philo < p->id_fork)
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(&p->left_fork);
		safe_print("has taken right fork", p);
		safe_print("has taken left fork", p);
	}
	else
	{	
		pthread_mutex_lock(&p->left_fork);	
		pthread_mutex_lock(p->right_fork);
		safe_print("has taken left fork", p);
		safe_print("has taken right fork", p);
	}
	pthread_mutex_lock(&p->d->mutex_for_dead);
	if (p->d->philo_dead)
	{
		pthread_mutex_unlock(&p->d->mutex_for_dead);
		let_go_forks(p);
		return (1);
	}
	pthread_mutex_unlock(&p->d->mutex_for_dead);
	return (0);
}

int	check_meal(t_philo *p, t_data *data)
{
	if (p->nb_eat > 0)
	{
		if (p->count_eat == p->nb_eat)
		{
			pthread_mutex_lock(&data->mutex_for_dead);
			if (!data->philo_dead)
			{
				pthread_mutex_lock(&p->d->mutex_for_count_meal);
				pthread_mutex_lock(&data->mutex_finish);
				if (data->count_meal == p->nb_eat)
				{
					data->finish = 1;
					pthread_mutex_lock(&p->d->mutex_for_print);
					ft_printf("simulation fini\n");
					pthread_mutex_unlock(&p->d->mutex_for_print);
				}
				pthread_mutex_unlock(&data->mutex_finish);
				pthread_mutex_unlock(&p->d->mutex_for_count_meal);
			}
			pthread_mutex_unlock(&p->d->mutex_for_dead);
			return (1);
		}
		return (0);
	}
	return (0);
}

int	smart_sleep(t_philo *p, size_t sleep_time)
{
	size_t	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < sleep_time)
	{
		pthread_mutex_lock(&p->d->mutex_for_dead);
		if (p->d->philo_dead)
		{
			pthread_mutex_unlock(&p->d->mutex_for_dead);
			return (1);
		}
		pthread_mutex_unlock(&p->d->mutex_for_dead);
		usleep(500);
	}
	return (0);
}

int	routine_philo(t_philo *p)
{
	pthread_mutex_lock(&p->d->last_eat_mutex);
	*p->last_eat = get_current_time();
	pthread_mutex_unlock(&p->d->last_eat_mutex);
	if (safe_print("is eating", p) == 0)
	{
		p->count_eat++;
		if (smart_sleep(p, p->time_to_eat))
		{
			let_go_forks(p);
			return (1);
		}
	}
	let_go_forks(p);
	if (safe_print("is sleeping", p) == 0)
		if (smart_sleep(p, p->time_to_sleep))
			return (1);
	return(safe_print("is thinking", p));
}

void	*routine(void *random)
{
	t_philo	*p;

	p = (t_philo *)random;
	// pthread_mutex_lock(&p->d->mutex_for_print);
	// ft_printf("nb eat %d, count eat %d, id_philo %d, id_fork %d\n", p->nb_eat, p->count_eat, p->id_philo, p->id_fork);
	// pthread_mutex_unlock(&p->d->mutex_for_print);
	if (only_one_philo(p))
		return (NULL);
	if ((p->id_philo % 2) == 0)
		usleep(1000);
	pthread_mutex_lock(&p->d->last_eat_mutex);
	*p->last_eat = get_current_time();
	pthread_mutex_unlock(&p->d->last_eat_mutex);
	pthread_create(&p->thread_eat, NULL, verif_dead, (void *)p);
	while (1)
	{
		if (check_meal(p, p->d))
			return (NULL);	
		if (take_fork(p))
			return (NULL);
		if (routine_philo(p) == 1)
			return (NULL);
		pthread_mutex_lock(&p->d->mutex_for_count_meal);
		if (p->count_eat == p->nb_eat)
			p->d->count_meal++;
		pthread_mutex_unlock(&p->d->mutex_for_count_meal);
	}
	return (NULL);
}
