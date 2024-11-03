# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <pthread.h>

#define MAX 100 //Could this value be a problem for larger size of N?
// #define output 1 //Comment this line to only collect the execution time
#define NUM_THREADS 4

typedef struct {
    int x, y;
} position;

typedef struct {
    int start_col;
    int *local_counter;
} thread_data;

int N = 0;
int total_counter = 0;
pthread_mutex_t mutex;

void SolveProblem(int n, int col_start, int *local_counter) {
    int counter1, counter2 = -1, counter3 = -1;
    int d[MAX][3] = {0};
    int *stack2 = (int *)malloc(n * sizeof(int));
    position Position1, Position2, Position3;
    position *head1 = (position *)malloc(n * n * sizeof(position));

    Position1.x = 0;
    Position1.y = col_start;
    head1[++counter2] = Position1;

    while (counter2 >= 0) {
        Position1 = head1[counter2--];

        while (counter3 >= 0 && Position1.x <= counter3) {
            Position2.x = counter3;
            Position2.y = stack2[counter3--];
            d[Position2.y][0] = 0;
            d[Position2.x + Position2.y][1] = 0;
            d[Position2.x - Position2.y + n][2] = 0;
        }

        stack2[++counter3] = Position1.y;
        d[Position1.y][0] = 1;
        d[Position1.x + Position1.y][1] = 1;
        d[Position1.x - Position1.y + n][2] = 1;

        if (counter3 == n - 1) {
            (*local_counter)++;
        } else {
            for (counter1 = n - 1; counter1 >= 0; counter1--) {
                if (d[counter1][0] == 0 && d[Position1.x + 1 + counter1][1] == 0 && d[n + Position1.x + 1 - counter1][2] == 0) {
                    Position3.x = Position1.x + 1;
                    Position3.y = counter1;
                    head1[++counter2] = Position3;
                }
            }
        }
    }

    free(stack2);
    free(head1);
}

void *thread_function(void *arg) {
    thread_data *data = (thread_data *)arg;
    int local_counter = 0;

    for(int i = data->start_col; i < N; i += NUM_THREADS) {
        SolveProblem(N, i, &local_counter);
    }

    pthread_mutex_lock(&mutex);
    total_counter += local_counter;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    if(argc == 2)
        N = atoi(argv[1]);
    else {
        printf("Please! Use: %s size_of_queens\n", argv[0]);
        return 1;
    }

    pthread_t threads[NUM_THREADS];
    thread_data thread_data_array[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    for(int i = 0; i < NUM_THREADS; i++) {
        thread_data_array[i].start_col = i;
        pthread_create(&threads[i], NULL, thread_function, (void *)&thread_data_array[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nTotal solutions: %d\n", total_counter);

    pthread_mutex_destroy(&mutex);
    return 0;
}
