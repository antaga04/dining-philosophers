// dining_philosophers_no_deadlock.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void *philosopher(void *num)
{
  int id = *(int *)num;
  while (1)
  {
    printf("Philosopher %d is thinking...\n", id);
    sleep(1);
    printf("Philosopher %d is hungry...\n", id);

    if (id == 0)
    {
      // Philosopher 0 picks up right fork first
      pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
      printf("Philosopher %d picked up right fork %d\n", id, (id + 1) % NUM_PHILOSOPHERS);
      pthread_mutex_lock(&forks[id]);
      printf("Philosopher %d picked up left fork %d\n", id, id);
    }
    else
    {
      // Other philosophers pick up left fork first
      pthread_mutex_lock(&forks[id]);
      printf("Philosopher %d picked up left fork %d\n", id, id);
      pthread_mutex_lock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
      printf("Philosopher %d picked up right fork %d\n", id, (id + 1) % NUM_PHILOSOPHERS);
    }

    // Eating
    printf("Philosopher %d is eating...\n", id);
    sleep(1);

    // Put down right fork
    pthread_mutex_unlock(&forks[(id + 1) % NUM_PHILOSOPHERS]);
    printf("Philosopher %d put down right fork %d\n", id, (id + 1) % NUM_PHILOSOPHERS);

    // Put down left fork
    pthread_mutex_unlock(&forks[id]);
    printf("Philosopher %d put down left fork %d\n", id, id);
  }
  return NULL;
}

int main()
{
  pthread_t philosophers[NUM_PHILOSOPHERS];
  int ids[NUM_PHILOSOPHERS];

  // Initialize mutexes
  for (int i = 0; i < NUM_PHILOSOPHERS; i++)
  {
    pthread_mutex_init(&forks[i], NULL);
  }

  // Create philosopher threads
  for (int i = 0; i < NUM_PHILOSOPHERS; i++)
  {
    ids[i] = i;
    pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
  }

  // Join philosopher threads
  for (int i = 0; i < NUM_PHILOSOPHERS; i++)
  {
    pthread_join(philosophers[i], NULL);
  }

  // Destroy mutexes
  for (int i = 0; i < NUM_PHILOSOPHERS; i++)
  {
    pthread_mutex_destroy(&forks[i]);
  }

  return 0;
}
