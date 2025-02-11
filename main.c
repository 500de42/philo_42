#include "philo.h"

void erreur_init_philo(t_philo **philo_list, int index)
{
    int i = -1;

    while(++i <= index)
    {
        free(philo_list[i]);
    }
    free(philo_list);
    philo_list = NULL;
}

void init_val_philo(t_philo **tmp, char **av, int i, int ac)
{
    (*tmp)->id_philo = i + 1;
    if (ac > 5)
        (*tmp)->finish_eat = ft_atoi(av[5]);
    else
        (*tmp)->finish_eat = 0;
    (*tmp)->nb_eat = 0;
    (*tmp)->ms_eat = 0;
    (*tmp)->time_to_dead = 0;
    (*tmp)->time_to_eat = 0;
    (*tmp)->time_to_sleep = 0;
}


void routine(t_philo **philo, char **av, t_data *data, t_val *timeval)
{
}

void init_philo(char **av, int ac, t_philo ***philo_list)
{
    t_philo     **tmp;
    int i;

    i = -1;
    *philo_list = malloc(sizeof (t_philo *) * ac);
    if (!philo_list)
        return ;
    tmp = *philo_list;
    while (++i < ac)
    {
        *tmp = malloc(sizeof (t_philo));
        if (!(*tmp))
        {
            erreur_init_philo(*philo_list, i);
            perror("error initialisation");
            exit(1) ;
        }
        init_val_philo(tmp, av, i, ac);
        pthread_mutex_init(&(*tmp)->left_fork, NULL);
        (*tmp)++;
    }
    *tmp == NULL;
}

int init_data_tv_time(t_val **tv, t_data **data)
{
    *tv = malloc (sizeof (t_val));
    if(!(*tv))
        return (1);
    *data = malloc (sizeof (t_data));
    if (!(*data))
        return (1);
    if (gettimeofday(&tv, NULL) == -1)
    {
        perror("gettimeofday failed");
        return (1);
    }
}

int main(int ac, char **av, char **env)
{
    t_philo     **philo_list;
    t_data      *data;
    t_val       *tv;

    init_data_tv_time(&tv, &data);
    check_arg(av, ac);
    init_philo(av, ac, &philo_list);
    routine(philo_list, av, data, tv);
}
