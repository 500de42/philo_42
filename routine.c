/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:01:09 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/11 17:36:50 by kcharbon         ###   ########.fr       */
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
		ft_printf("%d philo %d died\n", get_time_programme(p->d), p->id_philo);
		pthread_mutex_unlock(&p->d->mutex_for_print);
		pthread_mutex_unlock(&p->left_fork);
		return (1);
	}
	return (0);
}

int	forks(t_philo *p)
{
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
	return (safe_print("is thinking", p));
}

void	sleep_phi(t_philo *p)
{
	if (p->nb_philo > 30)
	{
		if ((p->id_philo % 2) == 0)
			usleep(p->time_before_dead);
	}
	else
	{
		if ((p->id_philo % 2) == 0)
			usleep(p->time_before_dead / 10);
	}
	pthread_mutex_lock(&p->d->last_eat_mutex);
	*p->last_eat = get_current_time();
	pthread_mutex_unlock(&p->d->last_eat_mutex);
}

void	*routine(void *random)
{
	t_philo	*p;

	p = (t_philo *)random;
	if (only_one_philo(p))
		return (NULL);
	sleep_phi(p);
	pthread_create(&p->thread_eat, NULL, verif_dead, (void *)p);
	while (1)
	{
		if (p->nb_philo % 2 && p->count_eat)
			smart_sleep(p, (p->time_before_dead - (p->time_to_eat
						+ p->time_to_sleep)) * 0.5);
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
