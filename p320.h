#ifndef _FILE_H
#define _FILE_H

int allocate_map();
int allocate_pid();
int search(int key, int l, int h);
void release_pid(int pid);

#endif