
#include "ping.h"

int loop = TRUE;

void	sigHandler(int signum)
{
	(void)signum;
	loop = FALSE;
}

void	init_structs(t_ping_info *ping, t_stats *data)
{
	ping->time = 0;
	ping->ttl = 0;
	ping->bytes_received = 0;
	ping->counter = 0;

	data->packets_sent = 0;
	data->packets_received = 0;
	data->times = NULL;
}

void	ping_loop(int ping_socket, struct sockaddr_in host_address, char *ip, char *name)
{
	t_ping_info	ping_data;
	t_stats		stats;

	init_structs(&ping_data, &stats);
	signal(SIGINT, sigHandler);

	printf("PING %s (%s): %d data bytes\n", name, ip, MSG_SIZE);
	while (loop)
	{
		send_ping(ping_socket, host_address, &ping_data);
		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", \
			ping_data.bytes_received, ip, ping_data.counter, ping_data.ttl, ping_data.time);
		sleep(PING_SLEEP);
		ping_data.counter++;
	}

	printf("--- %s ping statistics ---\n", name);
	//print_stats(stats);
}