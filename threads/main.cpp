#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <pthread.h>
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

#include "parallel.hpp"

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_S = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t lock_W = PTHREAD_COND_INITIALIZER;
volatile int dead_threads = 0;
volatile int jobCount = 0;
volatile int total_job_count = -1;

unsigned long long Q[MAX_TRIAL_COUNT];

void* run_trial_thread(void *arg) {
	while (1) {
		pthread_mutex_lock(&m);
		if (jobCount == total_job_count) {
			pthread_mutex_lock(&lock_S);
			dead_threads++;
			pthread_cond_signal(&lock_W);
			pthread_mutex_unlock(&m);
			pthread_mutex_unlock(&lock_S);
			pthread_exit((void*)0); //if no more jobs, just die
		}
		int pos = jobCount; //save this pos
		jobCount++; //we've taken this job
		pthread_mutex_unlock(&m);
		//do job
		int F[SIZE];
		init_pair(F);
		Q[pos] = find_perfect_matches(F);
		// printf("queries: %llu\n", Q[pos]);
	}
	return (void *)0;
}

void run_n_trials(int thread_count) {
	pthread_t tid[thread_count];
	//create N threads, each thread will run trials
	for (int i = 0; i < thread_count; ++i) {
		pthread_create(&tid[i], NULL, run_trial_thread, (void *)0);
	}
	pthread_mutex_lock(&lock_S);
	while (dead_threads != thread_count) {
		pthread_cond_wait(&lock_W, &lock_S);
    }
	pthread_mutex_unlock(&lock_S);
	for (int i = 0; i < thread_count; ++i) {
		pthread_join(tid[i], NULL);
	}
}

int main(int argc, char const *argv[]) {
	if (argc != 3) printf("usage: ./a.out [number of trials <= %d] [number of threads <= 12] ", MAX_TRIAL_COUNT), exit(0);
	srand(time(NULL));
	total_job_count = atoi(argv[1]); // perform M trials
	run_n_trials(atoi(argv[2]));
	unsigned long long sum = 0; // total number of queries
	for (int i = 0; i < total_job_count; ++i) {
		/*printf("Q[%d] = %llu\n", i, Q[i]);*/
		sum += Q[i];
	}
	printf("number of trials: %d\n", total_job_count);
	printf("expected number of queries: %f\n", (float)sum / total_job_count);
	return 0;
}