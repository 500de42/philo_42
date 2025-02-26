/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:01:09 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/26 20:01:37 by kcharbon         ###   ########.fr       */
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
		usleep(p->time_before_dead + 1);
		pthread_mutex_lock(&p->d->mutex_for_print);
		ft_printf("%d philo %d is dead\n", get_time_programme(p->d),
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

int	routine_philo(t_philo *p)
{
	pthread_mutex_lock(&p->d->last_eat_mutex);
	*p->last_eat = get_current_time();
	pthread_mutex_unlock(&p->d->last_eat_mutex);
	if (safe_print("is eating", p) == 0)
	{
		p->count_eat++;
		usleep(p->time_to_eat * 1000);
	}		
	pthread_mutex_lock(&p->d->mutex_for_print);
	ft_printf("DEBUG: tim_to_eat = %d, diff = %d,time_before_dead = %d,nb eat %d, count eat %d philo %d\n", p->time_to_eat, get_current_time()- *p->last_eat, p->time_before_dead, p->nb_eat, p->count_eat, p->id_philo);
	pthread_mutex_unlock(&p->d->mutex_for_print);
	let_go_forks(p);
	if (safe_print("is sleeping", p) == 0)
		usleep(p->time_to_sleep * 1000);
	if (safe_print("is thinking", p) == 1)
	{

		return (1);
	}
	else if (safe_print("is thinking", p) == 1)
		return (2);
	return (0);
}

void	*routine(void *random)
{
	t_philo	*p;

	p = (t_philo *)random;
	if ((p->id_philo % 2) == 0)
		usleep(p->time_before_dead);
	pthread_mutex_lock(&p->d->last_eat_mutex);
	*p->last_eat = get_current_time();
	pthread_mutex_unlock(&p->d->last_eat_mutex);
	pthread_create(&p->thread_eat, NULL, verif_dead, (void *)p);
	if (only_one_philo(p))
		return (NULL);
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

// ft_printf("DEBUG: last_eat address = %p, value = %d\n", p->last_eat,
// 	*p->last_eat);
// pthread_mutex_unlock(&p->d->mutex_for_print);
// pthread_mutex_lock(&p->d->mutex_for_print);
// ft_printf("DEBUG: current_time = %d, last_eat = %d, diff =
// 	%d,time_before_dead = %d\n",
// // 	get_current_time(), *p->last_eat, get_current_time()
// 		- *p->last_eat,p->time_before_dead);
// pthread_mutex_unlock(&p->d->mutex_for_print);
// // pthread_create(&p->thread_eat, NULL, verif_dead, p);
