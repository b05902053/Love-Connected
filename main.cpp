#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "constants.hpp"

using namespace std;

void init_pair(int F[SIZE])
{
	for (int i = 0; i < SIZE; i++) F[i] = i;
	random_shuffle(F, F + SIZE);
}

void print_matrix(int F[SIZE])
{
	int adj[SIZE][SIZE] = {{}};

	for (int i = 0; i < SIZE; i++) adj[i][F[i]] = 1;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++)
			printf("%d%c", adj[i][j], j == SIZE - 1 ? '\n': ' ');
	}
}

#include "naive.hpp"

int main(int argc, char *argv[])
{
	srand(0xada);
	static int F[SIZE];

	if (argc != 2) printf("usage: ./a.out [number of trials <= %d]\n", MAX_TRIAL_COUNT), exit(0);

	int trials = atoi(argv[1]); /* perform x trials */

	unsigned long long sum = 0; // total number of queries

	for (int i = 0; i < trials; i++)
	{
		init_pair(F);
		/* print_matrix(F); */
		unsigned long long q = find_perfect_matches(F);
		/* 
		 printf("Q[%d] = %llu\n", i, q);
		 */
		sum += q;
	}

	printf("number of trials: %d\n", trials);
	printf("expected number of queries: %f\n", (double)sum / trials);
}