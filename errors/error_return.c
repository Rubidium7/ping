
#include "ping.h"

int error_return(t_error code)
{

    if (code == ERROR_ARG_COUNT)
		  dprintf(STDERR_FILENO, "ping: missing host operand\n");	
    else if (code == ERROR_UNKNOWN_HOST)
		  dprintf(STDERR_FILENO, "ping: unknown host\n");	


    return (code);
}