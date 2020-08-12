#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX_MEALS 50
#define MAX_WAIT_TIME 3000000
#define NUMBER_OF_PHILOSOPHERS 7
#define WORK_TIME 3

enum states {
    THINKING, EATING, HUNGRY
};

struct TheDiningPhilosophers {
    pthread_mutex_t lock;
    enum states state[NUMBER_OF_PHILOSOPHERS];
    pthread_cond_t condition[NUMBER_OF_PHILOSOPHERS];
    long total_wait_time[NUMBER_OF_PHILOSOPHERS];
    long count[NUMBER_OF_PHILOSOPHERS];
};

struct TheDiningPhilosophers diningPhilosophers;

long wait_temp[NUMBER_OF_PHILOSOPHERS];

/* we will exit from a child thread without caring about memory leaks*/
void exit_gracefully() {
    long sum = 0;
    printf("Total waiting time: ");
    for (int k = 0; k < NUMBER_OF_PHILOSOPHERS; k++) {
        sum += diningPhilosophers.total_wait_time[k];
        printf("%f ", (float) diningPhilosophers.total_wait_time[k] / 1000000);
    }
    printf("\n Avg waiting time = %f\n", (float) sum / (NUMBER_OF_PHILOSOPHERS * 1000000));
    for (int k = 0; k < NUMBER_OF_PHILOSOPHERS; k++) {
        printf("%ld ", diningPhilosophers.count[k]);
    }
    printf("\n Ended successfully \n");
    exit(0);
}


/*Gets the clock time at this moment*/
long get_posix_clock_time() {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0) {
        return (long) (ts.tv_sec * 1000000000 + ts.tv_nsec);
    }
    return 0;
}

/*
Give way to neighbours if they are starving and have waited for a long time
*/
int self_run(int i) {
    long now = get_posix_clock_time();
    long n1 = 0, n2 = 0, cur = wait_temp[i] + now;
    if (diningPhilosophers.state[(i + 1) % NUMBER_OF_PHILOSOPHERS] == HUNGRY) {
        n1 = wait_temp[(i + 1) % NUMBER_OF_PHILOSOPHERS] + now;
        if (n1 > cur && n1 > MAX_WAIT_TIME) {
            printf("Philosopher %d giving way to %d to eat to AVOID starvation\n", i, (i + 1) % NUMBER_OF_PHILOSOPHERS);
            return 0;
        }
    }
    if (diningPhilosophers.state[(i + NUMBER_OF_PHILOSOPHERS - 1) % NUMBER_OF_PHILOSOPHERS] == HUNGRY) {
        n2 = wait_temp[(i + NUMBER_OF_PHILOSOPHERS - 1) % NUMBER_OF_PHILOSOPHERS] + now;
        if (n2 > cur && n2 > MAX_WAIT_TIME) {
            printf("Philosopher %d giving way to %d to eat to AVOID starvation\n", i, (i + NUMBER_OF_PHILOSOPHERS - 1) % NUMBER_OF_PHILOSOPHERS);
            return 0;
        }
    }
    return 1;
}

/*
Check if neighbours aren't eating and philosopher isn't starving
Change state to eating and signal the condition
*/
void check_chopsticks(int i) {
    printf("Philosopher %d looking for chopsticks\n", i);
    if (diningPhilosophers.state[i] == HUNGRY && (diningPhilosophers.state[(i + 1) % NUMBER_OF_PHILOSOPHERS] != EATING && diningPhilosophers.state[(i + NUMBER_OF_PHILOSOPHERS - 1) % NUMBER_OF_PHILOSOPHERS] != EATING) && self_run(i)) {
        diningPhilosophers.state[i] = EATING;

        //wait time is equal to start time - time at this moment
        wait_temp[i] += get_posix_clock_time();
        diningPhilosophers.total_wait_time[i] += wait_temp[i];
        //this does not unlock the mutex, need to unlock from parent function
        pthread_cond_signal(&diningPhilosophers.condition[i]);
    }
}

/*
Atomic call, change state of philosopher to thinking
Call the neighbours to check for free chopsticks
*/
void return_chopsticks(int philosopher_number) {
    static int meal_no = 0;

    pthread_mutex_lock(&diningPhilosophers.lock);
    diningPhilosophers.count[philosopher_number]++;
    diningPhilosophers.state[philosopher_number] = THINKING;
    printf("Philosopher %d finish eating\n", philosopher_number);

    meal_no++;
    printf("#Eating count = %d\n\n", meal_no);
    if (meal_no == MAX_MEALS) {
        exit_gracefully();
    }
    check_chopsticks((philosopher_number + NUMBER_OF_PHILOSOPHERS - 1) % NUMBER_OF_PHILOSOPHERS);
    check_chopsticks((philosopher_number + 1) % NUMBER_OF_PHILOSOPHERS);
    pthread_mutex_unlock(&diningPhilosophers.lock);
}

/*
Atomic call, the philosopher becomes hungry
Checks for free chopsticks, if not free then wait till signal
*/
void pickup_chopsticks(int philosopher_number) {
    pthread_mutex_lock(&diningPhilosophers.lock);
    diningPhilosophers.state[philosopher_number] = HUNGRY;
    printf("Philosopher %d is hungry\n", philosopher_number);

    // saving start time
    wait_temp[philosopher_number] = (-1) * get_posix_clock_time();

    check_chopsticks(philosopher_number);
    if (diningPhilosophers.state[philosopher_number] != EATING) {
        // need to already have the lock before calling this
        // release the lock, so that other threads can use shared data
        pthread_cond_wait(&diningPhilosophers.condition[philosopher_number], &diningPhilosophers.lock);
    }
    pthread_mutex_unlock(&diningPhilosophers.lock);
}

/*
Runs infinitely for all philosophers in different threads
Philosophers think and eat in this function
*/
void *philosopher(void *param) {
    int philosopher_number = *(int *) param;
    while (1) {
        srand(time(NULL) + philosopher_number);
        int think_time = (rand() % WORK_TIME) + 1;
        int eat_time = (rand() % WORK_TIME) + 1;
        diningPhilosophers.state[philosopher_number] = THINKING;
        printf("Philosopher %d is thinking for %d seconds\n", philosopher_number, think_time);
        sleep(think_time);
        pickup_chopsticks(philosopher_number);
        printf("Philosopher %d is eating for %d seconds\n", philosopher_number, think_time);
        sleep(eat_time);
        return_chopsticks(philosopher_number);
    }
}

int main() {
    /*Initialization code*/
    pthread_t tid[NUMBER_OF_PHILOSOPHERS];
    int id[NUMBER_OF_PHILOSOPHERS];
    pthread_mutex_init(&diningPhilosophers.lock, NULL);
    for (int j = 0; j < NUMBER_OF_PHILOSOPHERS; j++) {
        id[j] = j;
        diningPhilosophers.state[j] = THINKING;
        diningPhilosophers.count[j] = 0;
        diningPhilosophers.total_wait_time[j] = 0;
        wait_temp[j] = 0;
        pthread_create(&tid[j], NULL, &philosopher, &id[j]);
    }

    // main thread must keep running when other threads are running
    for (int j = 0; j < NUMBER_OF_PHILOSOPHERS; j++) {
        pthread_join(tid[j], NULL);
    }
}