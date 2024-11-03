#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAX 100 //Could this value be a problem for larger size of N?
// #define output 1 //Comment this line to only collect the execution time
#define NUM_THREADS 4

typedef struct {
    int x, y;
} position;

int N = 0;

void SolveProblem(int n, int col_start, int *local_counter) {
    int counter1, counter2 = -1, counter3 = -1;
    static int counter = 0;
    int d[MAX][3] = {0};
    int *stack2 = (int *)malloc(n*sizeof(int));
    position Position1, Position2, Position3;
    position *head1 = (position *)malloc(n*n*sizeof(position));

    Position1.x = 0;
    Position1.y = col_start;
    head1[++counter2] = Position1;

    while(counter2 >= 0){
        Position1 = head1[counter2--];

        while(counter3 >= 0 && Position1.x <= counter3){
            Position2.x = counter3;
            Position2.y = stack2[counter3--];
            d[Position2.y][0] = 0;
            d[Position2.x+Position2.y][1] = 0;
            d[Position2.x-Position2.y+n][2] = 0;
        }

        stack2[++counter3] = Position1.y;
        d[Position1.y][0] = 1;
        d[Position1.x+Position1.y][1] = 1;
        d[Position1.x-Position1.y+n][2] = 1;
        
        if(counter3 == n-1) {
            (*local_counter)++;
            #ifdef output
                printf("\n SOLUTION # %d:", *local_counter);
                for(counter1 = 0; counter1 <= counter3; counter1++)
                    printf("(%d,%d) ", counter1+1, stack2[counter1]+1);
            #endif

            Position2.x = counter3;
            Position2.y = stack2[counter3--];
            d[Position2.y][0] = 0;
            d[Position2.x+Position2.y][1] = 0;
            d[Position2.x-Position2.y+n][2] = 0;
        } else {
            for(counter1 = n-1; counter1 >= 0; counter1--) {
                if(d[counter1][0] == 0 && d[Position1.x+1+counter1][1] == 0 && d[n+Position1.x+1-counter1][2]==0) {
                    Position3.x = Position1.x+1;
                    Position3.y = counter1;
                    head1[++counter2] = Position3;
                }
            }
        }
    }
    
    free(stack2);
    free(head1);
}

int main(int argc, char **argv) {
    if(argc == 2)
        N = atoi(argv[1]);
    else {
        printf("Please! Use: %s size_of_queens\n", argv[0]);
        return 1;
    }

    omp_set_num_threads(NUM_THREADS);
    int total_counter = 0;

    #pragma omp parallel
    {
        int local_counter = 0;
        #pragma omp for schedule(static)
        for(int i = 0; i < N; i++) {
            SolveProblem(N, i, &local_counter);
        }
        
        #pragma omp atomic
        total_counter += local_counter;
    }

    printf("\nTotal solutions: %d\n", total_counter);

    return 0;
}
