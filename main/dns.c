
#include "ping.h"

char    *dns_lookup(char *name)
{
	struct hostent	*host;
    char            *ip;

	host = gethostbyname(name);
    if (!host)
		return (NULL);
	ip = malloc((strlen(inet_ntoa(*(struct in_addr *)host->h_addr_list[0])) + 1) * sizeof(char));
	if (!ip)
		error_exit(ERROR_MALLOC);
	strcpy(ip, inet_ntoa(*(struct in_addr *)host->h_addr_list[0]));

	return (ip);
}

char    *reverse_dns_lookup(char *ip)
{
	struct sockaddr_in 	tmp;
	struct in_addr addr;
	char    *name;
	char	buf[NI_MAXHOST];

	inet_pton(AF_INET, ip, &(addr.s_addr));
	tmp.sin_family = AF_INET;
	tmp.sin_port = htons(0);
	tmp.sin_addr = addr;
	if (getnameinfo((struct sockaddr *)&tmp, sizeof(tmp), buf, sizeof(buf), NULL, 0, 0))
		error_exit(ERROR_MALLOC);

	name = malloc((strlen(buf) + 1) * sizeof(char));
	strcpy(name, buf);
    return (name);
}
