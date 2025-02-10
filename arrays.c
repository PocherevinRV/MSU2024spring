#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20000 
#define L 20000
#define NUMBER_OF_TESTS 10
#define STATIC_ARRAY_CONST 100000

void test1(int **, const char *);
void test2(int **, const char *);
void test3(int *, const char *);
void test4(int *, const char *);
//void test1(int [N][L], const char *);
//void test2(int [N][L], const char *);
//void test1(int (*)[], const char *);
//void test2(int **, const char *);

void test1(int ** array, const char *test_info)
{
	int timer = 0, i, j;
	timer -= clock();
	for (int test_num = 0; test_num < NUMBER_OF_TESTS; test_num++) 
	{
		for (i=0; i < N; i++)
		{
			for (j=0; j < L; j++)
			{
				array[i][j] = L*i + j;
			}
		}
	}
	timer += clock();
	printf("Required time for %s: %f sec\n",test_info, ((double)timer)/CLOCKS_PER_SEC);
}

void test2(int ** array, const char *test_info)
{
	int timer = 0, i, j;
	timer -= clock();
	for (int test_num = 0; test_num < NUMBER_OF_TESTS; test_num++) 
	{
		for (j=0; j < L; j++)
		{
			for (i=0; i < N; i++)
			{
				array[i][j] = L*i + j;
			}
		}
	}
	timer += clock();
	printf("Required time for %s: %f sec\n",test_info, ((double)timer)/CLOCKS_PER_SEC);
}

void test3(int * array, const char *test_info)
{
	int timer = 0, i, j;
	timer -= clock();
	for (int test_num = 0; test_num < NUMBER_OF_TESTS; test_num++) 
	{
		for (i=0; i < N; i++)
		{
			for (j=0; j < L; j++)
			{
				array[L*i + j] = L*i + j;
			}
		}
	}
	timer += clock();
	printf("Required time for %s: %f sec\n",test_info, ((double)timer)/CLOCKS_PER_SEC);
}


void test4(int * array, const char *test_info)
{
	int timer = 0, i, j;
	timer -= clock();
	for (int test_num = 0; test_num < NUMBER_OF_TESTS; test_num++) 
	{
		for (j=0; j < L; j++)
		{
			for (i=0; i < N; i++)
			{
				array[L*i + j] = L*i + j;
			}
		}
	}
	timer += clock();
	printf("Required time for %s: %f sec\n",test_info, ((double)timer)/CLOCKS_PER_SEC);
}



int main(void)
{         
	int i;

	//int a1[N][L];
	//int a2[N*L];
	int* a3;

	int (*a4)[L];   	
	int *a5[N]; 
	int *a6[N];

	int **a7;
	int **a8;	
        
		
	//test3(a2, "a2 (rows)");
	//test4(a2, "a2 (columns)");
        
        a3 = (int *) malloc (N*L*sizeof(int));
        test3(a3, "a3 (rows)");
	test4(a3, "a3 (columns)");
        free(a3);
	
	a4 = (int (*)[L]) malloc (N*L*sizeof(int));

	free(a4);
	
	
		for (i=0; i < N; i++) {a5[i] = (int *) malloc (L*sizeof(int));} 

	for (i=0; i < N; i++) {free(a5[i]);}                          

	a6[0] = (int *) malloc (N*L*sizeof(int));
	for (i=1; i < N; i++) {a6[i] = a6[i-1] + L;} 
	
	free(a6[0]);	a7 = (int **) malloc (N*sizeof(int *));
	for (i=0; i < N; i++) {a7[i] = (int *)malloc(L*sizeof(int));}
	test1(a7, "a7 (rows)");
	test2(a7, "a7 (columns)"); 
	for (i=0; i < N; i++) {free(a7[i]);}	
	free(a7);
	
	a8 = (int **) malloc (N*sizeof(int *) + N*L*sizeof(int));
	a8[0] = (int *)(a8 + N);
	for (i=1; i < N; i++) {a8[i] = a8[i-1] + L;}
	test1(a8, "a8 (rows)");
	test2(a8, "a8 (columns)"); 	
	free(a8);
           
	return 0;
}