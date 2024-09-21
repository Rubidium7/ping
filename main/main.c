
#include "ping.h"

// struct hostent {
//                char  *h_name;            /* official name of host */
//                char **h_aliases;         /* alias list */
//                int    h_addrtype;        /* host address type */
//                int    h_length;          /* length of address */
//                char **h_addr_list;       /* list of addresses */
//            }


void	print_array(char **array)
{
	for (size_t i = 0; array[i]; i++)
	{
		printf("%s\n", array[i]);
	}

}

int main(int ac, char **av)
{
	struct hostent *host;

	if (ac < 2)
	{
		dprintf(STDERR_FILENO, "ping: missing host operand\n");	
		return (ERROR_ARG_COUNT);
	}

	host = gethostbyname(av[1]);
	if (!host)
	{
		dprintf(STDERR_FILENO, "ping: unknown host\n");	
		return (ERROR_UNKNOWN_HOST);
	}
	printf("%s\n", host->h_name);
	printf("%s\n", inet_ntoa(*(struct in_addr *)host->h_addr_list[0]));

	return (0);
}
