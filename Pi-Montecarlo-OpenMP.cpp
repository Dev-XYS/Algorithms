#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
float randNumGen(){

   int random_value = rand(); //Generate a random number
   float unit_random = random_value / (float) RAND_MAX; //make it between 0 and 1
   return unit_random;
}
int main (int argc, char *argv[]) {

    int i, z = 0, threads = 8, iters = 100000;
    double x,y, pi;

    #pragma omp parallel private(i,x,y) reduction(+:z) num_threads(threads)
        for (i=0; i<iters; ++i) {
            #pragma omp critical
            {
                x = randNumGen();
                y = randNumGen();
            }
            if ((x*x+y*y) <= 1.0)
                z++;
        }

    pi = ((double) z / (double) (iters*threads))*4.0;
    printf("Pi: %lf\n", pi);;
    return 0;
}
