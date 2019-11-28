#include <stdio.h>
#include <stdlib.h>

double	ft_atof(char *str)
{
	double f;
	double div;
	double neg;

	f = 0.0;
	neg = 1.0;
	if (str && *str == '-')
	{
		neg = -1.0;
		str++;
	}
	while (str && *str && *str != '.' && *str >= '0' && *str <= '9')
		f = f * 10 + *str++ - '0';
	div = 0.1;
	while (str && *(++str) && *str >= '0' && *str <= '9')
	{
		f += ((*str - '0') * div);
		div /= 10.0;
	}
	return (f * neg);
}

int main() {

		printf("%f\n", ft_atof("50.6"));

	return 0;
}
