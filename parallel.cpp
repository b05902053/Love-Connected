#include "constants.hpp"
#include "parallel.hpp"
#include <cstdio>


#define NUM 10
#define PAR 1

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

static void fill_matrix(bool matrix[SIZE][SIZE], int r, int c)
{
	for (int j = 0; j < SIZE; j++) matrix[r][j] = true;

	for (int i = 0; i < SIZE; i++) matrix[i][c] = true;
}

unsigned long long find_perfect_matches(int F[SIZE])
{
	static bool matrix[SIZE][SIZE];
	static bool matched[SIZE];
	int m[NUM];
	int n[NUM];
	int place;
	int count = 0;
	int round = 0;
	int r, c;
	int st = -1;

	for (int i = 0; i < SIZE; i++)
		for (int j = 0; j < SIZE; j++)
			matrix[i][j] = false;

	for (int i = 0; i < SIZE; i++) matched[i] = false;

	while (count < SIZE - 1)
	{
		round++;
		int cnt = 0;
		int p_cnt;
		int start = 0;
		bool toSelect = true;
		int ii;

		while (cnt < NUM)
		{
			if (toSelect) {
				ii = -1;
				for (int i = start; i < SIZE && ii == -1; i++) {
					if (matched[i]) continue;
					ii = i;
					start = i + 1;
				}
				toSelect = false;
				place = ii * SIZE - 1;
				p_cnt = 0;
				continue;
			}
			
			place = next_place(matrix, place + 1);

			if (place < 0) break;

			r = place / SIZE;
			c = place % SIZE;
			if (r != ii) {
				toSelect = true;
				continue;
			}
			
			m[cnt] = r; n[cnt] = c;
			matrix[r][c] = true;
			cnt++;
			p_cnt++;
			if (p_cnt == PAR) {
				toSelect = true;
				continue;
			}
		}

		if (cnt < NUM && place < 0) {
			place = st;
			while (cnt < NUM) {
				place = next_place(matrix, place + 1);
				if (place < 0) break;
				st = place;
				m[cnt] = place / SIZE;
				n[cnt] = place % SIZE;
				cnt++;
			}
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