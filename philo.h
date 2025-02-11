#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int id_philo;
	pthread_t philo;
	int time_to_dead;
	int time_to_eat;
	int time_to_sleep;
	long int ms_eat;
	long int last_eat;
	unsigned int nb_eat;
	int finish_eat;
	pthread_mutex_t *right_fork;
	pthread_mutex_t left_fork;
} t_philo;

typedef struct s_data
{
	pthread_mutex_t mutex_for_print;
	size_t starting_time;
	int nb_philo;
} t_data;

int	init_data(t_data **data, size_t time_, char **av);
void	check_arg(char **av, int ac);
void	init_val_philo(t_philo **tmp, char **av, int i, int ac);
void	init_philo(char **av, int ac, t_philo ***philo_list, t_data *data);
size_t	get_current_time(void);
size_t	get_time_programme(t_data *data);
void	loop_for_wait_philo(t_philo **philo, t_data *data);
void	*routine(void *arg);
void	create_thread(t_philo **philo, char **av, t_data *data);

////////////////////    erreurs     ///////////////////////

void	erreur_init_philo(t_philo **philo_list, int index);

#endif
