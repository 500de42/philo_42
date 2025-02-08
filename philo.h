/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 19:10:18 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/08 22:39:26 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct t_philo
{
	int				id_philo;
	int				time_to_dead;
	int				time_to_eat;
	int				time_to_sleep;
	long int        ms_eat;     // time of the last dinner in milliseconds
	unsigned int    nb_eat;	// number of dinners (each time the philosopher eats nb_eat++)
	int             finish;          // 1 when a philosopher ate m_eat times, if not, 0
	pthread_mutex_t	*r_f;
	pthread_mutex_t	l_f;
}					t_philo;

void				check_arg(char **av, int ac);

#endif
