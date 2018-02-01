// compiles with:
// g++ slow_code.cpp -o slow_code


#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>

void get_walltime(double* wcTime) {

     struct timeval tp;

     gettimeofday(&tp, NULL);

     *wcTime = (double)(tp.tv_sec + tp.tv_usec/1000000.0);
}

// complex algorithm for evaluation
void myfunc(std::vector<std::vector<int> > &b,std::vector<int> &a,std::vector<int> &c)
{ 
	//Outer Looping
	double d_val;
	int size =a.size();
	int mysize=b[0].size();	

	for (int i = 0; i < size; i+=2)
	{
		for (int j = 0; j < mysize; j++)
		{				
			c[i]=c[i]+b[j][i]*a[j];
			c[i+1]=c[i+1]+b[j][i+1]*a[j]; 
		}
	}

	/*int bs = 10;
	int size = a.size();
	int nb = size/bs;

	for (int k =1; k <=nb; k+=1){
		for (int i = 0; i <size; i+=2){
			for (int j = (k-1)*bs+1; j < k*bs; j+=1){
				c[i]=c[i]+b[j][i]*a[j];
				c[i+1]=c[i+1]+b[j][i+1]*a[j];
			}
		}
	}*/

}

int main(int argc, char *argv[])
{

	// this should be called as> ./slow_code <i_R> <i_N>

	int i_R = 1000;	
	int i_N = 10;
	double d_S, d_E;

	// parse input parameters 
	if (argc >= 2)
	{
		i_R = atoi(argv[1]);
	}

	if (argc >= 3)
	{
		i_N = atoi(argv[2]);
	}

	// some declarations
	std::vector<std::vector<int> > b(i_N, std::vector<int>(i_N) );
	std::vector<int> a(i_N);
	std::vector<int> c(i_N);
	// populate memory with some random data
	for (int i = 0; i < i_N; i++)
	{
		c[i] = i * i;
		a[i] = i*i;
		for (int j = 0; j < i_N; j++)
			b[i][j] = j + i;
	}

	// start benchmark
	get_walltime(&d_S);

	// iterative test loop
	for (int i = 0; i < i_R; i++)
	{
		myfunc(b, a, c);
	}

	// end benchmark
	get_walltime(&d_E);

	// report results
	printf("Elapsed time: %f\n", d_E - d_S);

	return 0;
}
