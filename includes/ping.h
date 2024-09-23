
#ifndef PING_H
# define PING_H

# include "defines.h"
# include "structs.h"
# include <netdb.h>
# include <arpa/inet.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/socket.h>
# include <netinet/ip_icmp.h>
# include <sys/time.h>
# include <errno.h>

//ping.c
void	send_ping(int ping_socket, struct sockaddr_in host_address, t_ping_info *ping);

//ping_loop.c
void	ping_loop(int ping_socket, struct sockaddr_in host_address, char *ip, char *name);

//dns.c
char    *dns_lookup(char *name, struct sockaddr_in *host_address);
char    *reverse_dns_lookup(char *ip);

//error_return.c
int error_return(t_error code);

//fatal_error.c
void error_exit(t_error code);

//base_printing_utils.c
void	print_array(char **array);

#endif
