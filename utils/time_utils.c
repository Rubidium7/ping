#include "ping.h"

float	time_diff(struct timeval before, struct timeval after)
{
	float sec_diff = after.tv_sec - before.tv_sec;
	float usec_dif = after.tv_usec - before.tv_usec;
	
	return (sec_diff * 1000 + usec_dif / 1000);
}

t_time	*new_time_node(float time)
{
	t_time	*new_node;

	new_node = malloc(sizeof(t_time));
	if (!new_node)
		return (NULL);
	new_node->time = time;
	new_node->next = NULL;
	return (new_node);
}

void	append_time(t_stats *stats, float time)
{
	t_time	*current = stats->times;

	if (!current)
	{
		stats->times = new_time_node(time);
		if (!stats->times)
		{
			dprintf(STDERR_FILENO, "time node failed to get created\n");
			return ;
		}
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_time_node(time);
		if (!current->next)
		{
			dprintf(STDERR_FILENO, "time node failed to get created\n");
			return ;
		}
	}
}

void	print_time_stats(t_time *times)
{
	t_time	*current = times;
	float	max = -1;
	float	min = NONE;
	float	all = 0;
	int		n = 0;

	while (current)
	{
		if (current->time > max)
			max = current->time;
		if (min == NONE || min > current->time)
			min = current->time;
		all += current->time;
		n++;
		current = current->next;
	}
	float avg = all / n;
	float stddev = calculate_standard_deviation(times, avg, n);
	printf("round-trip min/avg/max/stddev = ");
	printf("%.3f/%.3f/%.3f/%.3f ms\n", min, avg, max, stddev);
}