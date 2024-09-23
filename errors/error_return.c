
#include "ping.h"

int error_return(t_error code)
{

    if (code == ERROR_ARG_COUNT)
		dprintf(STDERR_FILENO, "ping: missing host operand\n");	
    else if (code == ERROR_UNKNOWN_HOST)
		dprintf(STDERR_FILENO, "ping: unknown host\n");
	else if (code == ERROR_SOCKET)
		dprintf(STDERR_FILENO, "fatal error: socket failed to be created\n");
	else if (code == ERROR_SETSOCKOPT)
		dprintf(STDERR_FILENO, "fatal error: setsockopt failed\n");


    return (code);
}