#include "ping.h"

void	send_ping(int ping_socket, struct sockaddr_in host_address, char *ip, t_stats *stats)
{
	t_ping_packet			packet;
	int						i;
	char					buffer[BUFFER_SIZE];
	struct sockaddr_in		src_address;
	ssize_t					bytes;
	float					time;
	struct timeval			time_before;
	struct timeval			time_after;

	bzero(&packet, sizeof(packet));
	for (i = 0; i != MSG_SIZE - 1; i++)
		packet.msg[i] = 'a';
	packet.msg[i] = 0;
	packet.header.type = ICMP_ECHO;
	packet.header.un.echo.id = getpid();
	packet.header.un.echo.sequence = stats->counter;
	packet.header.checksum = checksum(&packet, sizeof(packet));

	gettimeofday(&time_before, NULL);
	if (sendto(ping_socket, &packet, sizeof(packet), 0, (struct sockaddr*)&host_address, sizeof(host_address)) < 0)
	{
		printf("packet didn't get sent\n");
		return ;
	}
	else
		stats->packets_sent++;
	unsigned int src_size = sizeof(src_address);
	bzero(buffer, sizeof(buffer));
	bytes = recvfrom(ping_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&src_address, &src_size);
	if (bytes <= 0)
		printf("failed to get an answer\n");
	else
	{
		gettimeofday(&time_after, NULL);
		time = time_diff(time_before, time_after);
		stats->packets_received++;
		append_time(stats, time);
		bytes -= 20;
		struct icmphdr *recv_header = (struct icmphdr *)(buffer + 20);
		struct iphdr *ipb = (struct iphdr *)(recv_header + 8);
		if (recv_header->type || recv_header->code)
			printf("unexpected response, type: %d code: %d\n", recv_header->type, recv_header->code);
		else
		{
			printf("%ld bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", \
			bytes, ip, stats->counter, ipb->ttl, time);
		}
	}


}