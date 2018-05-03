#include "smlist.h"
#include <time.h>
#include <ctype.h>
#define NUM 1000000

void sm_memcpy(void* dest, void* src, size_t size) {
	unsigned char* pd=(unsigned char*)dest;
	unsigned char* ps=(unsigned char*)src;
	while(size--) {
		*pd++=*ps++;
	}
}

int main() {

	uint32_t i=0;// int result;

	NODE node= {0};

	clock_t cl_before, cl_after;

	cl_before=clock();

	float alloc_time, free_time;

	for(i = 0; i < NUM; i++) sm_list_push_front(&node, sm_list_alloc_node(&i, sizeof(i)));


	cl_after=clock();

	alloc_time=(cl_after-cl_before)/(float)CLOCKS_PER_SEC;

	cl_before=clock();
    
	sm_list_clear(&node);

	cl_after=clock();
	free_time=(cl_after-cl_before)/(float)CLOCKS_PER_SEC;

    
	printf("alloc: %f sec\nfree: %f sec\n", alloc_time, free_time);

	return 0;
}
