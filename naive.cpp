#include "constants.hpp"
#include "naive.hpp"
#include <cstdio>

#define NUM 10

static void fill_matrix(bool matrix[SIZE][SIZE], int r, int c)
{
	for (int j = 0; j < SIZE; j++) matrix[r][j] = true;

	for (int i = 0; i < SIZE; i++) matrix[i][c] = true;
}
static int next_place(bool matrix[SIZE][SIZE], int start)
{
	int place = start;

	int r, c;
	while (1)
	{
		r = place / SIZE; c = place % SIZE;
		if (r >= SIZE) return -1;
		if (matrix[r][c]) {
			place++;
			continue;
		}

		return place;
	}
}

unsigned long long find_perfect_matches(int F[SIZE])
{
	static bool matrix[SIZE][SIZE];
	int count = 0;
	int round = 0;
	int place = -1;
	int m[NUM];
	int n[NUM];
	int r, c;

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			matrix[i][j] = false;

	while (count < SIZE - 1)
	{
		round++;
		int cnt = 0;
		while (cnt < NUM)
		{
			place = next_place(matrix, place + 1);
			if (place < 0) break;

			m[cnt] = place / SIZE;
			n[cnt] = place % SIZE;
			cnt++;
		}

		for (int i = 0; i < cnt; i++) {
			if (F[m[i]] == n[i]) {
				fill_matrix(matrix, m[i], n[i]);
				count++;
			}
		}

		#ifdef DEBUG
		printf("query: \n");
		for (int i = 0; i < cnt; i++)
			printf("%d %d\n", m[i], n[i]);
		puts("end");

		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				printf("%d%c", matrix[i][j], j == SIZE - 1 ? '\n': ' ');
		printf("place = %d\n", place);
		#endif
	}

	return round;
}