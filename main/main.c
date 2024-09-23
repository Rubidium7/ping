
#include "ping.h"

// struct hostent {
//                char  *h_name;            /* official name of host */
//                char **h_aliases;         /* alias list */
//                int    h_addrtype;        /* host address type */
//                int    h_length;          /* length of address */
//                char **h_addr_list;       /* list of addresses */
//            }

int main(int ac, char **av)
{
	char 				*ip;
	char				*name;
	int					ping_socket;
	struct sockaddr_in	host_address;
	int					ttl = TTL;
	struct timeval		tv;
	
	tv.tv_sec = TIMEOUT;
	tv.tv_usec = 0;


	if (ac < 2)
		return (error_return(ERROR_ARG_COUNT));

	ip = dns_lookup(av[1], &host_address);
	if (!ip)
		return (error_return(ERROR_UNKNOWN_HOST));

	name = strdup(av[1]);
	//name = reverse_dns_lookup(ip);
	//printf("%s\n%s\n", ip, name);
	
	ping_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (ping_socket < 0)
		return (error_return(ERROR_SOCKET));

	if (setsockopt(ping_socket, SOL_IP, IP_TTL, &ttl, sizeof(ttl)))
		return error_return(ERROR_SETSOCKOPT);
	if (setsockopt(ping_socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv)))
		return error_return(ERROR_SETSOCKOPT);

	ping_loop(ping_socket, host_address, ip, name);


	free(ip);
	free(name);
	return (0);
}
