/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:01:58 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/13 21:40:06 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_thread(t_philo **philo, t_data *data)
{
	int	i;

	i = -1;
	if (pthread_create(&data->philo_get, NULL, routine_thread,
			NULL) != 0)
	{
		ft_putstr_fd("error creation pthread_getteur\n", 2);
		// fonction qui clear tout
		return ;
	}
	while (++i < data->nb_philo)
	{
		data->i = i;
		data->philo_list[i]->i = i;
		if (pthread_create(&philo[i]->philo, NULL, routine, NULL) != 0)
		{
			ft_putstr_fd("error creation pthread\n", 2);
			// fonction qui clear tout
			return ;
		}
	}
}

void	loop_for_wait_philo(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philo[i]->philo, NULL) != 0)
		{
			ft_putstr_fd("error pthread_join", 2);
			// fonction qui clean tout
		}
		i++;
	}
	if (pthread_join(data->philo_get, NULL) != 0)
	{
		ft_putstr_fd("error pthread_join philo get", 2);
		// fonction qui clean tout
	}
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_time_programme(t_data *data)
{
	return ((get_current_time()) - data->starting_time);
}

int	get_dead_time(t_data *data, int i)
{
	size_t	is_dead;

	is_dead = (size_t)get_current_time - data->philo_list[i]->last_eat;
	if (is_dead >= (size_t)data->time_to_dead)
		return (1);
	return (0);
}
