
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

//dns.c
char    *dns_lookup(char *name);
char    *reverse_dns_lookup(char *ip);

//error_return.c
int error_return(t_error code);

//fatal_error.c
void error_exit(t_error code);

//base_printing_utils.c
void	print_array(char **array);

#endif
