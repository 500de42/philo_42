/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharbon <kcharbon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:31:18 by kcharbon          #+#    #+#             */
/*   Updated: 2025/03/11 17:38:13 by kcharbon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				i;
	int				time_to_dead;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_philo;
	int				count_meal;
	int				finish;
	bool			philo_dead;
	size_t			starting_time;
	pthread_mutex_t	mutex_finish_eat;
	pthread_mutex_t	mutex_for_time;
	pthread_mutex_t	mutex_for_dead;
	pthread_mutex_t	mutex_for_print;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	mutex_for_count_meal;
	pthread_mutex_t	mutex_finish;
}					t_data;

typedef struct s_philo
{
	int				id_philo;
	int				id_fork;
	int				i;
	int				philo_dead;
	int				time_before_dead;
	int				time_to_eat;
	int				time_to_sleep;
	int				count_eat;
	int				nb_eat;
	int				nb_philo;
	int				finish_eat;
	pthread_t		philo;
	pthread_t		thread_eat;
	size_t			*last_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	t_data			*d;
}					t_philo;

int					init_data(t_data **data, char **av);
void				check_arg(char **av, int ac);
void				init_val_philo(t_philo *tmp, char **av, int i, int ac);
void				init_philo(char **av, int ac, t_philo ***philo_list,
						t_data *data);
size_t				get_current_time(void);
size_t				get_time_programme(t_data *data);
int					get_dead_time(t_data *data, t_philo *philo_list);
void				loop_for_wait_philo(t_philo **philo, t_data *data);
void				*routine(void *random);
void				create_thread(t_philo **philo, t_data *data);
void				*verif_dead(void *random);
int					only_one_philo(t_philo *p);
int					take_fork(t_philo *p);
int					routine_philo(t_philo *p);
int					check_meal(t_philo *p, t_data *data);
int					safe_print(char *str, t_philo *ph);
void				let_go_forks(t_philo *p);
int					smart_sleep(t_philo *p, size_t sleep_time);
void				erreur_init_philo(t_philo **philo_list, int index);
void				in(char **av, t_philo ***philo_list, t_data *data);
void				free_(t_philo ***philo_list, int a, t_data *data, bool f);
int					forks(t_philo *p);
void				split_meal(t_philo *p, t_data *data);
void				sleep_phi(t_philo *p);
void				destroy_data(t_data *data);
void				p(char *str, t_philo *ph, t_data *data, size_t time);

#endif
