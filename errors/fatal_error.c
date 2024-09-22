
#include "ping.h"

void error_exit(t_error code)
{

    if (code == ERROR_MALLOC)
			dprintf(STDERR_FILENO, "fatal error: malloc failes\n");

    exit(1);
}