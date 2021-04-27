/* gmtime example */
#include <stdio.h> // puts, printf
#include <time.h> // time_t, strcut tm, time, gmtime

#define MST (-7)
#define UTC (0)
#define CCT (+8)
#define KST (+9)

int main(void)
{
	time_t rawtime;
	struct tm * ptm;

	time(&rawtime);
	ptm = gmtime(&rawtime);

	puts("Current time around the World:");
	printf("Phoenix, AZ (U.S.) : %2d:%02d\n", (ptm->tm_hour+MST)%24, ptm->tm_min);
	printf("Reykjavik (Iceland) : %2d:%02d\n", (ptm->tm_hour+UTC)%24, ptm->tm_min);
	printf("Beijing (China) : %2d:%02d\n", (ptm->tm_hour+CCT)%24, ptm->tm_min);
	printf("Seoul (Korea) : %2d:%02d\n", (ptm->tm_hour+KST)%24, ptm->tm_min);
}