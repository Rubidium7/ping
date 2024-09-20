
#include "ping.h"

int main(int ac, char **av)
{
	if (ac < 2)
	{
		dprintf(STDERR_FILENO, "ping: missing host operand\n");	
		return (64);
	}

	return (0);
}
