#include "ping.h"

unsigned short checksum(void *packet, int len)
{
    unsigned short	*buf = packet;
    unsigned int	sum = 0;
    unsigned short	result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}


float	calculate_standard_deviation(t_time *times, float avg, int n)
{
	float	devs_added = 0;
	float	deviation;

	while (times)
	{
		deviation = (times->time - avg) * (times->time - avg);
		devs_added += deviation;
		times = times->next;
	}

	float mutsis = sqrtf(devs_added / n);

	return (mutsis);
}