#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_data
{

	int				i;
	int				time_to_dead;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_philo;
	int				count_meal;
	bool 			philo_dead;
	size_t			starting_time;
	pthread_mutex_t	mutex_for_dead;
	pthread_mutex_t	mutex_for_print;
	pthread_mutex_t	dead_time_mutex;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	mutex_for_count_meal;
}					t_data;

typedef struct s_philo
{
	int				id_philo;
	int				i;
	int				philo_dead;
	int				time_before_dead;
	int				time_to_eat;
	int				time_to_sleep;
	long int		ms_eat;
	unsigned int	count_eat;
	int 			nb_eat;
	pthread_t		philo;
	pthread_t		philo_get;
	size_t			*last_eat;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	left_fork;
	t_data			*d;
}					t_philo;

int					init_data(t_data **data, char **av);
void				check_arg(char **av, int ac);
void				init_val_philo(t_philo *tmp, char **av, int i, int ac);
void				init_philo(char **av, int ac, t_philo ***philo_list, t_data *data);
size_t				get_current_time(void);
size_t				get_time_programme(t_data *data);
int					get_dead_time(t_data *data, t_philo *philo_list);
void				loop_for_wait_philo(t_philo **philo, t_data *data);
void				*routine(void * random);
void				create_thread(t_philo **philo, t_data *data);
void				*verif_dead(void *random);
void				ft_usleep(long int time_in_ms);
int					only_one_philo(t_philo *p);
void				take_fork(t_philo *p);
void				routine_philo(t_philo *p);
int					check_meal(t_philo *p, int nb_eat, t_data *data);
int    				safe_print(char *str, t_philo *ph);

////////////////////    erreurs     ///////////////////////

void				erreur_init_philo(t_philo **philo_list, int index);
#endif
