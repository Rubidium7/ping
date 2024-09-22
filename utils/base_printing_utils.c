
#include "ping.h"

void	print_array(char **array)
{
	for (size_t i = 0; array[i]; i++)
	{
		printf("%s\n", array[i]);
	}

}

