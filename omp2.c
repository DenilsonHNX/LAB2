#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define TOTALSIZE 1000
#define NUMITER 200
#define f(x,y) ((x + y) / 2.0)
int main(int argc, char *argv[]) {
    int i, iter;
    double *V1 = (double *) malloc(TOTALSIZE * sizeof(double));
    double *V2 = (double *) malloc(TOTALSIZE * sizeof(double));
    double *curr = V1, *next = V2, *temp;

    
    for (i = 0; i < TOTALSIZE; i++) {
        V1[i] = (double)i;
    }

    
    for (iter = 0; iter < NUMITER; iter++) {
        #pragma omp parallel for
        for (i = 0; i < TOTALSIZE - 1; i++) {
            next[i] = f(curr[i], curr[i + 1]);
        }

        
        next[TOTALSIZE - 1] = curr[TOTALSIZE - 1];

       
        temp = curr;
        curr = next;
        next = temp;
    }

   
    printf("Output:\n");
    for (i = 0; i < TOTALSIZE; i++) {
        printf("%4d %f\n", i, curr[i]);
    }

    
    free(V1);
    free(V2);

    return 0;
}
