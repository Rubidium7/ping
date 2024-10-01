#include "ping.h"

int	send_ping(int ping_socket, struct sockaddr_in host_address, char *ip, t_stats *stats)
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
		return (TRUE);
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
		struct ip *recv_ip_hdr = (struct ip *) buffer;
		int header_len = recv_ip_hdr->ip_hl << 2;

		if (recv_ip_hdr->ip_p != IPPROTO_ICMP)
			return (TRUE);

		struct icmp *recv_icmp_hdr = (struct icmp *)(buffer + header_len);

		if (bytes - header_len < 16 || recv_icmp_hdr->icmp_id != getpid())
			return (TRUE);
			
		if (recv_icmp_hdr->icmp_type == ICMP_ECHO)
		{
			stats->packets_sent--;
			return (FALSE);
		}
		gettimeofday(&time_after, NULL);
		time = time_diff(time_before, time_after);
		stats->packets_received++;
		append_time(stats, time);
		if (recv_icmp_hdr->icmp_type != ICMP_ECHOREPLY || recv_icmp_hdr->icmp_code)
			printf("unexpected response, type: %d code: %d\n", recv_icmp_hdr->icmp_type, recv_icmp_hdr->icmp_code);
		else
		{
			printf("%ld bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", \
			bytes - header_len, ip, recv_icmp_hdr->icmp_seq, recv_ip_hdr->ip_ttl, time);
		}
	}

	return (TRUE);
}