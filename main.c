#include "RSA.h"

unsigned long long
factorize(unsigned long long n)
{
	unsigned long long sqrt_n = sqrt(n);
	unsigned long long factor = 2;
	unsigned int remainder;

	while (factor <= sqrt_n)
	{
		remainder = n % factor;
		if (remainder == 0)
		{
			return (factor);
		}
		factor++;
	}
	return (n);
}

int
main(int argc, char *argv[])
{
	FILE *file;
	char *filename = argv[1];
	char *line = NULL;
	size_t size = 0;
	ssize_t nchars;
	unsigned long long p, q, n;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: factors <file>\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Unable to open file: %s\n", filename);
		exit(EXIT_FAILURE);
	}

	while ((nchars = getline(&line, &size, file)) != -1)
	{
		n = strtoull(line, NULL, 10);
		p = factorize(n);
		q = n / p;
		fprintf(stdout, "%llu=%llu*%llu\n", n, q, p);
	}

	fclose(file);
	exit(EXIT_SUCCESS);
}
