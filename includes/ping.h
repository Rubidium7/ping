
#ifndef PING_H
# define PING_H

# include "defines.h"
# include "structs.h"
# include <netdb.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/socket.h>
# include <netinet/ip_icmp.h>
# include <sys/time.h>
# include <errno.h>

//ping.c
void	send_ping(int ping_socket, struct sockaddr_in host_address, char *ip, t_stats *stats);

//ping_loop.c
void	ping_loop(int ping_socket, struct sockaddr_in host_address, char *ip, char *name);

//dns.c
char    *dns_lookup(char *name, struct sockaddr_in *host_address);
char    *reverse_dns_lookup(char *ip);

//error_return.c
int error_return(t_error code);

//fatal_error.c
void error_exit(t_error code);

//math_utils.c
unsigned short	checksum(void *packet, int len);
float			calculate_standard_deviation(t_time *times, float avg, int n);

//time_utils.c
float	time_diff(struct timeval before, struct timeval after);
void	append_time(t_stats *stats, float time);
void	print_time_stats(t_time *times);

//base_printing_utils.c
void	print_array(char **array);

#endif
