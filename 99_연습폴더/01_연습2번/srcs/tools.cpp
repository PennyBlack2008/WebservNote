#include "miniserv.hpp"

char	*ft_memset(char *mem, int c, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		mem[i] = c;
		i++;
	}
	return (mem);
}
