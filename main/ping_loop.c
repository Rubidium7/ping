
#include "ping.h"

int loop = TRUE;

void	sigHandler(int signum)
{
	(void)signum;
	loop = FALSE;
}

void	init_stats(t_stats *stats)
{
	stats->packets_sent = 0;
	stats->packets_received = 0;
	stats->times = NULL;
	stats->counter = 0;
}

void	print_stats(t_stats stats)
{
	int		lost_packets = stats.packets_sent - stats.packets_received;
	int		packet_loss = 0;

	if (stats.packets_sent)
		packet_loss = (lost_packets * 100) / stats.packets_sent;

	printf("%d packets transmitted, %d packets received, %d%% packet loss\n", \
	 stats.packets_sent, stats.packets_received, packet_loss);

	print_time_stats(stats.times);
}

void	ping_loop(int ping_socket, struct sockaddr_in host_address, char *ip, char *name)
{
	t_stats		stats;

	init_stats(&stats);
	signal(SIGINT, sigHandler);

	printf("PING %s (%s): %d data bytes\n", name, ip, MSG_SIZE);
	while (loop)
	{
		send_ping(ping_socket, host_address, ip, &stats);
		sleep(PING_SLEEP);
		stats.counter++;
	}

	printf("--- %s ping statistics ---\n", name);
	print_stats(stats);
}