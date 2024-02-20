#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 40

void print_symbols(const char *);
int read_file(const char *);
int str_test(const char *);

void print_symbols(const char * filename)
{
	FILE *file = fopen(filename, "w");
	for (int i = 0; i < 256; i++) fprintf(file, "Symbol #%d is [%c]\n", i, i);
	fclose(file);
}

int read_file(const char * filename)
{
	char c;
	FILE *file = fopen(filename, "r");
	if (!file) return -1;
	printf("File text:\n");
	while (!feof(file)) 
	{
		c = fgetc(file);
		printf("%c", c);
	}
	printf("\nEnd of file\n");
	return 0;
}

int str_test(const char *filename)
{
	char * str1, * str2;
	FILE *file = fopen(filename, "r");
	str1 = (char *)malloc(STR_LEN * sizeof(char));
	str2 = (char *)malloc((STR_LEN + 5) * sizeof(char));
	if (!file) return -1;
	fgets(str1, STR_LEN, file);
	printf("str1 = [%s]\n", str1);
	strcpy(str2, "New ");
	printf("str2 = [%s]\n", str2);
	strcat(str2, str1);
	printf("str2 + str1 =[%s]\n", str2);
	printf("str1 == str2: %d\n", strcmp(str1, str2));
	printf("str2 == str2: %d\n", strcmp(str2, str2));
	printf("len(str1) = %d, len(str2) = %d\n", (int)strlen(str1), (int)strlen(str2));
	return 0;
}

int main(void)
{
	print_symbols("symbols.txt");
	read_file("text.txt");
	str_test("text.txt");
	return 0;
}