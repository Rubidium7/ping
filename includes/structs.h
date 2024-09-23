
#ifndef STRUCTS_H
# define STRUCTS_H


# include <netinet/ip_icmp.h>

typedef enum e_error
{
    ERROR_UNKNOWN_HOST = 1,
    ERROR_MALLOC,
	ERROR_SOCKET,
	ERROR_SETSOCKOPT,
    ERROR_ARG_COUNT = 64,
}   t_error;

typedef struct s_ping_packet
{
	struct icmphdr	header;
	char			msg[MSG_SIZE];
}	t_ping_packet;

typedef struct s_ping_info
{
	float time;
	int ttl;
	int bytes_received;
	int counter;
}	t_ping_info;

typedef struct s_time
{
	float			time;
	struct s_time	*next;
}	t_time;

typedef struct s_stats
{
	int 	packets_sent;
	int 	packets_received;
	t_time	*times;
}	t_stats;

#endif