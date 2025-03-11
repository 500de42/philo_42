/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:47:04 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/11 17:34:18 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	p(char *str, t_philo *ph, t_data *data, size_t time)
{
	pthread_mutex_lock(&data->mutex_for_print);
	ft_printf("%d the philo %d %s\n", time, ph->id_philo, str);
	pthread_mutex_unlock(&data->mutex_for_print);
}

int	safe_print(char *str, t_philo *ph)
{
	size_t	time;
	t_data	*data;

	data = ph->d;
	pthread_mutex_lock(&data->mutex_for_dead);
	pthread_mutex_lock(&data->mutex_finish);
	if (data->philo_dead == true || ((ph->count_eat == ph->nb_eat)
			&& (ph->nb_eat > 0)) || data->finish == 1)
	{
		pthread_mutex_unlock(&data->mutex_for_dead);
		if (data->finish)
		{
			pthread_mutex_unlock(&data->mutex_finish);
			return (1);
		}
		pthread_mutex_unlock(&data->mutex_finish);
		if (ph->count_eat == ph->nb_eat)
			return (2);
		return (1);
	}
	pthread_mutex_unlock(&data->mutex_finish);
	pthread_mutex_unlock(&data->mutex_for_dead);
	time = get_time_programme(data);
	p(str, ph, data, time);
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
	if ((p->id_philo % 2) == 0)
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(&p->left_fork);
		safe_print("has taken left fork", p);
		safe_print("has taken right fork", p);
	}
	else
	{
		pthread_mutex_lock(&p->left_fork);
		pthread_mutex_lock(p->right_fork);
		safe_print("has taken right fork", p);
		safe_print("has taken left fork", p);
	}
	if (forks(p))
		return (1);
	return (0);
}

void	let_go_forks(t_philo *p)
{
	if (p->id_philo % 2 == 0)
	{
		pthread_mutex_unlock(&p->left_fork);
		pthread_mutex_unlock(p->right_fork);
	}
	else
	{
		pthread_mutex_unlock(p->right_fork);
		pthread_mutex_unlock(&p->left_fork);
	}
}

void	erreur_init_philo(t_philo **philo_list, int index)
{
	int	i;

	i = -1;
	while (++i <= index)
	{
		free(philo_list[i]);
	}
	free(philo_list);
	philo_list = NULL;
}
