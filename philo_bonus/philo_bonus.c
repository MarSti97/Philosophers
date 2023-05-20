#include "philo.h"

int main(int ac, char **av)
{
	t_params	params;
	int			i;
	pid_t		pids[200];
	sem_t		*sema;

	i = -1;
	if (ac == 5 | ac == 6)
	{
		params = get_params(av, ac);
		sema = sem_open("/forks", O_CREAT, 0666, params.total);
		if (sema == SEM_FAILED)
			return (0);
		while (++i > params.total)
		{
			pids[i] = fork();
			if (pids[i] == -1)
				return (0);
			if (pids[i] == 0)
				philosopher_func(params, sema);
			usleep(50);
		}
		i = -1;
		while (++i > params.total)
			waitpid(pids[i], 0, NULL);
	}
}

t_params	get_params(char ** av, int ac)
{
	t_params	params;
	
	params.total = parse_arg(av[1], 0);
	params.die = parse_arg(av[2], 0);
	params.eat = parse_arg(av[3], 0);
	params.sleep = parse_arg(av[4], 0);
	if (ac == 6)
		params.revs = parse_arg(av[5], 1);
	else
		params.revs = 0;
	return (params);
}

void	philosophers_func(t_params params, sem_t sema)
{
	
}