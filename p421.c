#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int avg=0;
int min=0;
int max=0;
int size=0;

void* average(void* arr) {
	
	char **array = (char**) arr;
	int sum = 0;
	for (int i = 1; i <= size; ++i)
	{
		sum = sum + atoi(array[i]);
	}
	avg = sum / (size);
	pthread_exit(0);
}

void* minimum(void* arr) {
	
	char **array = (char**) arr;
	int smallest;
	
	smallest = atoi(array[1]);
	
	for (int i = 2; i <= size; ++i)
	{
		if (smallest > atoi(array[i])) smallest = atoi(array[i]); 
	}
	min = smallest;
	pthread_exit(0);
}

void* maximum(void* arr) {

	char **array = (char**) arr;
	int largest;
	
	largest = atoi(array[1]);
	
	for (int i = 2; i <= size; ++i)
	{
		if (largest < atoi(array[i])) largest = atoi(array[i]); 
	}
	max = largest;
	pthread_exit(0);
}

int main(int argc, char* argv[]) {

	size = argc - 1;

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;

	pthread_create(&thread1, NULL, average, argv);
	pthread_create(&thread2, NULL, minimum, argv);
	pthread_create(&thread3, NULL, maximum, argv);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	printf("The average value is %d\n", avg);
	printf("The minimum value is %d\n", min);
	printf("The maximum value is %d\n", max);

 }