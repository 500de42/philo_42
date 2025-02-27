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

void	ft_free_array(char **tab);

int	main(int ac, char **av)
{
	t_data *data;
	t_philo	**philo_list;

	check_arg(av, ac);
	init_data(&data, av);
	init_philo(av, ac, &philo_list, data);
	create_thread(philo_list, data);
	loop_for_wait_philo(philo_list, data);
}
