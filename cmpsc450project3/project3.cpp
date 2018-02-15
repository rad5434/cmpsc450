#include <omp.h>
#include <stdio.h>
static long num_steps = 1000000000;
double step;
#define NUM_THREADS 3
// define some space between our summing variables to
// alleviate false sharing
#define SPAN 64

int main(void)
{
	int i_numThreads;
	double pi;
	// step will be shared (read) among all threads
	step = 1.0 / (double) num_steps;
	omp_set_num_threads(NUM_THREADS);
	// sum will be shared among all threads
	// each thread will write into a separate array element
	double d_sum[NUM_THREADS][SPAN];
	#pragma omp parallel
	{
		// declare some private variables
		int i, i_nthreads, i_ID;
		double x;
		// this will range from 0 to nThreads
		i_ID = omp_get_thread_num();
		// get total number of threads since
		// we aren't guaranteed what we request
		i_nthreads = omp_get_num_threads();
		// limit writing to numThreads to a single thread
		if (i_ID == 0) i_numThreads = i_nthreads;
		for (i = i_ID; i < num_steps; i+=i_nthreads)
		{
			x = (i+0.5) * step;
			d_sum[i_ID][0] = d_sum[i_ID][0] + 4.0 / (1.0 + x*x);
		}
	}
	// finish the summation by summing the individual results of the threads
	for (int i = 0; i < i_numThreads; i++)
		pi += d_sum[i][0] * step;
	printf("PI = %0.9f\n", pi);
}