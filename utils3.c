/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:34:37 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/11 17:36:52 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	split_meal(t_philo *p, t_data *data)
{
	pthread_mutex_lock(&data->mutex_finish);
	data->finish = 1;
	pthread_mutex_unlock(&data->mutex_finish);
	pthread_mutex_lock(&p->d->mutex_for_print);
	ft_printf("simulation fini\n");
	pthread_mutex_unlock(&p->d->mutex_for_print);
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
				pthread_mutex_lock(&data->mutex_finish_eat);
				p->finish_eat = 1;
				pthread_mutex_unlock(&data->mutex_finish_eat);
				pthread_mutex_lock(&p->d->mutex_for_count_meal);
				pthread_mutex_lock(&p->d->mutex_for_print);
				ft_printf("le philo %d a manger %d, count meal %d\n",
					p->id_philo, p->count_eat, data->count_meal);
				pthread_mutex_unlock(&p->d->mutex_for_print);
				if (data->count_meal == p->nb_philo)
					split_meal(p, data);
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
