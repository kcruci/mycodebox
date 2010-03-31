#include <stdio.h>
#include <string.h>
#include <linux/types.h>
#include "jhash.h"

int main(int argc, char **argv)
{
	char *s1 = "asdfghjkl";
	char *s2 = "iud8fmndd";
	unsigned int v1 = jhash(s1, strlen(s1), 0);
	unsigned int v2 = jhash(s2, strlen(s2), 0);
	printf("%X, %X\n", v1, v2);
	return 0;
}
