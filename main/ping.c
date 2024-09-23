#include "ping.h"

unsigned short checksum(void *packet, int len) {
    unsigned short	*buf = packet;
    unsigned int	sum = 0;
    unsigned short	result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

void	send_ping(int ping_socket, struct sockaddr_in host_address, t_ping_info *ping)
{
	t_ping_packet			packet;
	int						i;
	int						failed = FALSE;
	char					buffer[BUFFER_SIZE];
	struct sockaddr_in		src_address;

	bzero(&packet, sizeof(packet));
	for (i = 0; i != MSG_SIZE - 1; i++)
		packet.msg[i] = 'a';
	packet.msg[i] = 0;
	packet.header.type = ICMP_ECHO;
	packet.header.un.echo.id = getpid();
	packet.header.un.echo.sequence = ping->counter;
	packet.header.checksum = checksum(&packet, sizeof(packet));


	if (sendto(ping_socket, &packet, sizeof(packet), 0, (struct sockaddr*)&host_address, sizeof(host_address)) < 0) {
		failed = TRUE;
	}
	unsigned int src_size = sizeof(src_address);
	bzero(buffer, sizeof(buffer));
	if (recvfrom(ping_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&src_address, &src_size) <= 0)
		printf("Fail\n");
	else
	{

		if (!failed)
		{
			struct icmphdr *recv_header = (struct icmphdr *)buffer;
			printf("type = %d code = %d\n", recv_header->type, recv_header->code);
		}
	}


}