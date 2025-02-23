/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:01:09 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/23 21:49:30 by kcharbon         ###   ########.fr       */
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
		ft_usleep(p->time_before_dead + 1);
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("%d philo %d is dead\n", get_time_programme(p->d),
			p->id_philo);
		pthread_mutex_unlock(&p->d->mutex_for_print);
		return (1);
	}
	return (0);
}

int	take_fork(t_philo *p)
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
	else
	{
		pthread_mutex_unlock(&p->d->mutex_for_dead);
		return (1);
	}
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
				if (data->count_meal == p->nb_eat)
				{
					pthread_mutex_lock(&p->d->mutex_for_print);
					ft_printf("simulation fini\n");
					pthread_mutex_unlock(&p->d->mutex_for_print);
				}
				pthread_mutex_unlock(&p->d->mutex_for_count_meal);
			}
			pthread_mutex_unlock(&p->d->mutex_for_dead);
			return (1);
		}
		return (0);
	}
	return (0);
}

int	routine_philo(t_philo *p)
{
	if (take_fork(p))
		return (1);
	*p->last_eat = get_current_time();
	pthread_mutex_lock(&p->d->mutex_for_dead);
	if (!p->d->philo_dead)
	{
		pthread_mutex_unlock(&p->d->mutex_for_dead);
		pthread_create(&p->thread_sleep, NULL, verif_dead, (void *)p);
	}
	else
	{
		// pthread_mutex_lock(&p->d->mutex_for_print);
		// ft_printf("\n\n%d\n\n", p->d->philo_dead);
		// pthread_mutex_unlock(&p->d->mutex_for_print);
		pthread_mutex_unlock(&p->d->mutex_for_dead);
		let_go_forks(p);
		return (1);
	}
	if (!safe_print("is eating", p))
		ft_usleep(p->time_to_eat);
	else
	{
		let_go_forks(p);
		return (1);
	}
	let_go_forks(p);
	pthread_mutex_lock(&p->d->mutex_for_dead);
	if (!p->d->philo_dead)
	{
		pthread_mutex_unlock(&p->d->mutex_for_dead);
		pthread_create(&p->thread_sleep, NULL, verif_dead, (void *)p);
	}
	else
	{
		pthread_mutex_unlock(&p->d->mutex_for_dead);
		return (1);
	}
	if (!safe_print("is sleeping", p))
		ft_usleep(p->time_to_sleep + 1);
	else
		return (1);
	if (safe_print("is thinking", p))
		return (1);
	pthread_mutex_lock(&p->d->mutex_for_dead);
	if (!p->d->philo_dead)
	{
		pthread_mutex_unlock(&p->d->mutex_for_dead);
		return (1);
	}
	return (0);
}

void	*routine(void *random)
{
	t_philo	*p;
	int		nb_eat;

	nb_eat = 0;
	p = (t_philo *)random;
	pthread_mutex_lock(&p->d->last_eat_mutex);
	*p->last_eat = get_current_time();
	pthread_mutex_unlock(&p->d->last_eat_mutex);
	if ((p->id_philo % 2) == 0)
		ft_usleep(p->time_before_dead / 10);
	if (only_one_philo(p))
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&p->d->mutex_for_dead);
		if (p->d->philo_dead)
		{
			pthread_mutex_unlock(&p->d->mutex_for_dead);
			return (NULL);
		}
		pthread_mutex_unlock(&p->d->mutex_for_dead);
		if (check_meal(p, p->d))
			return (NULL);
		if (routine_philo(p))
			return (NULL);
		p->count_eat++;
	}
	return (NULL);
}
