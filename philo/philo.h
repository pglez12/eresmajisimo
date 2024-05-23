/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 09:16:16 by payllana          #+#    #+#             */
/*   Updated: 2024/05/14 11:52:04 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

# define K	1000

enum	e_state{
	NOT_PRINT,
	SLEEP,
	EAT,
	THINK,
	DIE,
	TAKE,
	UNTAKE
};

# define SLEEP_MSG	"is sleeping"
# define EAT_MSG	"is eating"
# define THINK_MSG	"is thinking"
# define TAKE_MSG	"has taken a fork"
# define UNTAKE_MSG	"drop a fork"
# define DIE_MSG	"died"

typedef struct s_info {
	long	num_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_must_eat;
}	t_params;

typedef struct s_msg {
	pthread_mutex_t	*print;
	long			time;
	long			ph;
	long			flag;
	char			*msg;
}	t_msg;

typedef struct s_philo {
	pthread_mutex_t	*print;
	pthread_mutex_t	*count_mutex;
	pthread_mutex_t	*left_mutex;
	pthread_mutex_t	*right_mutex;
	pthread_mutex_t	*flag_mutex;
	t_params		info;
	long			*left_fork;
	long			*right_fork;
	long			ph_name;
	long			*n_finish_eating;
	long			init_usec;
	long			n_philo_eat;
	int				*flag;
}	t_philo;

size_t		ft_strlen(const char *s);
int			ft_isdigit(int c);
int			ft_isspace(char s1);
long		ft_atol(const char *str);
void		ft_putstr_fd(char *s, int fd);

int			ft_turn_mic(char *argv, long *value, int mul);
long		ft_time_now(void);

t_philo		*ft_init_philo(int argc, char **argv);
int			ft_creat_philos(t_philo *philo, pthread_t **id_th);

int			ft_check_int(const char *input, long *output);
int			ft_check_args(int argc, char **argv, t_params *info);
int			ft_init_params(int argc, char **argv, t_params *info);

void		ft_pause_philo(t_philo *ph, long start_time, long cmp_time);
int			ft_check_philo(t_philo *ph, long start_time, int flag);
void		*ft_philo(void *input);

int			ft_eat(t_philo *ph, long *start_time);
int			ft_sleep(t_philo *ph, long start_time);
int			ft_think(t_philo *ph, long start_time);

int			ft_check_die(t_philo *ph);
int			ft_eat_right_mutex(t_philo *ph, long start_time);
int			ft_padlock_fmutex(pthread_mutex_t *fork, long *flag);

int			ft_set_phmsg(t_philo *ph, t_msg *msg, int flag);
int			ft_philo_msg(t_philo *ph, t_msg *msg);

void		ft_free_id(pthread_t **id_threads, long size);
void		ft_free_philo(t_philo *philo);

#endif
