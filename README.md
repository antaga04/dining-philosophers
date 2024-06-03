
Implement the Dining Philosophers problem using POSIX threads. The forks should be a 5-element mutex array (pthread_mutex_lock and pthread_mutex_unlock functions) and each philosopher should be a separate thread. Create two solutions:

1) With a deadlock possibility: each philosopher with a number i=0...4 takes the left fork first (mutex with index i) and then the right fork (mutex with index (i+1)%5). Demonstrate the occurrence of the deadlock.

2) Modify the first solution by introducing an asymmetry: One of the philosopher should take the forks in a reverse order: the right fork first, then the left one. Is this modification sufficient to prevent a deadlock? What about starvation?