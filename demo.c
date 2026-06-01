#include <stddef.h>
#include <stdio.h>
#include "diff_vector.h"
#include <unistd.h>
#include <time.h>

#define SIZE 1000000

void vector_print(Vector *vec) {
	for(int i = 0; i < vec->count; i++) {
		printf("vec value %d: %d\n", i, *(int *)(vec->values+(i*vec->item_size)));
	}
}


int main() {
	clock_t begin = clock();

	Vector *map = vector_new(sizeof(Vector *));
	int tmp = 10;
	for(int x = 0; x < 10; x++) {
		Vector *row = vector_new(sizeof(int));
		for(int y = 0; y < 10; y++) {
			vector_add(row, &tmp);
		}
		vector_add(map, &row);
	}
	int replace = 5;
	vector_replace2d(map, 3, 3, &replace);
	for(int x = 0; x < 10; x++) {
		for(int y = 0; y < 10; y++) {
			printf("%d ", *(int *)vector_get2d(map, x, y));
		}
		printf("\n");
	}
	
	Vector *vec = vector_new(sizeof(int));
	printf("vectors created!\n");
	printf("size = %d\n", SIZE);
	int b = 5;
	for(int i = 0; i < SIZE; i++) {
		int a = 23;
		vector_add(vec, &a);
	}
	printf("printing vec..\n");
	//vector_print(vec);
	vector_add(vec, &b);
	vector_add(vec, &b);
	vector_add(vec, &b);
	vector_remove(vec, &b);
	vector_remove(vec, &b);
	vector_add(vec, &b);
	//vector_print(vec);
	vector_free(vec);
	vector2d_free(map);
	printf("done\n");
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time spent: %f\n", time_spent);
//	sleep(3000);
}
