/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:47:04 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/11 18:47:29 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
