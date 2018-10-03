#include <stdio.h>
#include <stdlib.h>
#include "p320.h"

#define MIN_PID 300
#define MAX_PID 5000

typedef struct PID {
	int pid;
	int availability;
}PID;

const int size = MAX_PID - MIN_PID + 1;
PID *bitmap[MAX_PID - MIN_PID + 1];
int counter = 0;

int allocate_map() {

	int pid = MIN_PID;
	
	for (int i = 0; i < size; i++) {

		PID *newpid = (PID*)malloc(sizeof(PID)); 
		
		newpid->pid = pid;
		newpid->availability = 0;

		bitmap[i] = newpid;
		pid++;
	}
	printf("Map allocation successful!\n");
	return 0;
 }
 //circular styled algorithm for making sure released keys can be reused
int allocate_pid() {

	for (int i = 0; i < size; i++) {

		if (bitmap[counter % size]->availability == 0) {
			
			int j = counter;

			bitmap[j % size]->availability = 1;
			printf("Allocating pid: %d\n", bitmap[j % size]->pid);

			counter++; 
			return bitmap[j % size]->pid;
		}
		counter++;
	}
      //if, after 'size' iterations, every key availability is set to zero, key structure is full 
	  printf("exhausted Pid range! No more Pids available\n");
	  return -1; 
  }
//search for the correct key index
int search(int key, int l, int h) {

	int mid = l + (h-l) / 2;

	if ( mid == 0 && (key != bitmap[mid]->pid) ) {
		printf("PID not found!\n");
		return 0;
	}
	else if (key > bitmap[mid]->pid) { 
		l = mid + 1;
		search(key, l, h);
	}
	else if (key < bitmap[mid]->pid) {
		h = mid - 1;
		search(key, l, h);
	} 
	else return mid; 
}
//sets key availabilit to zero
void release_pid(int pid) {

	if ( pid < MIN_PID || pid > MAX_PID) { printf("Out of range key!\n"); return; }

	int i = search(pid, 0, size);
	
	if (bitmap[i]->pid != pid) { //if BS returns incorrect key, key doesnt exist
		printf("key not found...\n");
		return;
	}
	printf("Releasing pid: %d\n",bitmap[i]->pid );
	bitmap[i]->availability = 0;
	return;
}

/*int main(void) {

	allocate_map();

	for (int i = 0; i < size; ++i) 
	{
		allocate_pid();
	}
	allocate_pid();
	release_pid(28374);

	for (int i = 0; i < size; ++i)
	{
		printf("%d %d\n",bitmap[i]->pid, bitmap[i]->availability);
		release_pid(bitmap[i]->pid);
	}
	for (int i = 0; i < size; ++i)
	{
		printf("%d %d\n",bitmap[i]->pid, bitmap[i]->availability);
	}
	for (int i = 0; i < size; ++i) 
	{
		allocate_pid();
	}
	for (int i = 0; i < size; ++i)
	{
		printf("%d %d\n",bitmap[i]->pid, bitmap[i]->availability);
		release_pid(bitmap[i]->pid);
	}
	return 0;
}*/