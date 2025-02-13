/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:45:38 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/13 21:31:43 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_val_philo(t_philo *tmp, char **av, int i, int ac)
{
	tmp->id_philo = i + 1;
	if (ac == 6)
		tmp->nb_eat = ft_atoi(av[5]);
	else
		tmp->nb_eat = 0;
	tmp->count_eat = 0;
	tmp->ms_eat = 0;
	tmp->time_before_dead = ft_atoi(av[2]);
	tmp->time_to_eat = ft_atoi(av[3]);
	tmp->time_to_sleep = ft_atoi(av[4]);
	tmp->i = i;
	pthread_mutex_init(&tmp->left_fork, NULL);
}

void	init_philo(char **av, int ac, t_data *data)
{
	int	i;

	i = -1;
	data->philo_list = malloc(sizeof(t_philo *) * (data->nb_philo + 1));
	if (!data->philo_list)
	{
		// fonction qui free tout
		return ;
	}
	while (++i < data->nb_philo)
	{
		data->philo_list[i] = malloc(sizeof(t_philo));
		if (!data->philo_list[i])
		{
			erreur_init_philo(data->philo_list, i);
			ft_putstr_fd("error initialisation", 2);
			exit(1);
		}
		init_val_philo(data->philo_list[i], av, i, ac);
	}
	data->philo_list[i] = NULL;
	i = -1;
	while (++i < data->nb_philo)
	{
		if (ft_atoi(av[1]) > 1)
		{
			if (i == 0)
				data->philo_list[i]->right_fork = &data->philo_list[ft_atoi(av[1])
					- 1]->left_fork;
			else
				data->philo_list[i]->right_fork = &data->philo_list[i
					- 1]->left_fork;
		}
	}
}

int	init_data(t_data **data, size_t time_, char **av)
{
	*data = malloc(sizeof(t_data));
	if (!(*data))
		return (1);
	(*data)->starting_time = time_;
	(*data)->nb_philo = ft_atoi(av[1]);
	(*data)->time_to_dead = ft_atoi(av[2]);
	(*data)->time_to_sleep = ft_atoi(av[4]);
	(*data)->time_to_eat = ft_atoi(av[3]);
	pthread_mutex_init(&(*data)->mutex_for_print, NULL);
	return (0);
}
