#ifndef PHILO_H
# define PHILO_H

// # include "libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id_philo;
    pthread_t		philo;
	int				time_to_dead;
	int				time_to_eat;
	int				time_to_sleep;
	long int        ms_eat;
	long int		last_eat;
	unsigned int    nb_eat;
	int             finish_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
}					t_philo;

typedef struct timeval
{
    time_t      tv_sec;   // Secondes depuis 1970
    suseconds_t tv_usec;  // Microsecondes (1/1 000 000 s)
}				t_val;

typedef struct s_data
{
	pthread_mutex_t	mutex_for_print;
	long			starting_time;
}					t_data;

void				check_arg(char **av, int ac);
void				init_val_philo(t_philo **tmp, char **av, int i, int ac);
void				init_philo(char **av, int ac, t_philo ***philo_list);
////////////////////    erreurs     ///////////////////////
void				erreur_init_philo(t_philo **philo_list, int index);
#endif
