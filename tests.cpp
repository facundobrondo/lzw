#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// Programa que va a generar archivos de prueba llamados tests/test-nn
// de tamaño 2^nn
int main(int argc, const char * argv[])
{
	int i, j, max;
	int max_files;
	FILE * f;
	char str[20];
	char c;

	if (argc != 2)
		return 1;

	max_files = strtol(argv[1], NULL, 10);

	for (i = 0; i <= max_files; i++) {
		sprintf(str, "%s%02d", "tests/test-", i);
		printf("%s\n", str);

		f = fopen(str, "wb");

		if (i == 0)
			max = 0;
		else
			max = pow(2, i);

		for (j = 0; j < max; j++) {
			c = j % 256;
			fwrite(&c, sizeof(char), 1, f);
		}

		fclose(f);
	}

	return  0;
}
