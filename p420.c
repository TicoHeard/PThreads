#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "p320.h"

void* runPID(void* time) {
	
	int pid = allocate_pid();
	sleep( *( (int*)time) );
	release_pid(pid);
	
	pthread_exit(0);
}

int main(int argc, char *argv[]) {

	if (argc < 2) {printf("Must be second argument specifying number of threads\n"); return 0;}
	
	allocate_map();
	
	int num_threads = atoi(argv[1]);
	pthread_t threads[num_threads];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	srand( time(0) );
	int passed;

	for (int i = 0; i < num_threads; ++i)
	{
		unsigned r = rand() % 10; //fix this
		passed = pthread_create(&threads[i], &attr, runPID, &r);
		assert(!passed);
	}

	for (int i = 0; i < num_threads; ++i)
	{
		passed = pthread_join(threads[i], NULL);
		assert(!passed);	
	}

	printf("All threads executed successfully.\n");
	return 0;
}