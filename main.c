/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/02/11 18:15:40 by kcharbon          #+#    #+#             */
/*   Updated: 2025/02/11 18:15:40 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data *data;
	size_t time_;

	time_ = get_current_time();
	// check_arg(av, ac);
	init_data(&data, time_, av);
	init_philo(av, ac, data);
	create_thread(data->philo_list, data);
	loop_for_wait_philo(data->philo_list, data);
}
