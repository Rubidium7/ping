
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
	char 	*ip;
	char	*name;

	if (ac < 2)
		return (error_return(ERROR_ARG_COUNT));

	ip = dns_lookup(av[1]);
	if (!ip)
		return (error_return(ERROR_UNKNOWN_HOST));

	name = reverse_dns_lookup(ip);
	printf("%s\n%s\n", ip, name);
	
	free(ip);
	free(name);
	return (0);
}
