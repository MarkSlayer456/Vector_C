#include <stddef.h>
#include <stdio.h>
#include "vector.h"

void vector_print(Vector *vec) {
	for(int i = 0; i < vec->count; i++) {
		printf("vec value %d: %d\n", i, *(int *)vec->values[i]);
	}
}


int main() {
	Vector *map = vector_new(sizeof(Vector));
	int tmp = 10;
	for(int x = 0; x < 10; x++) {
		Vector *row = vector_new(sizeof(int));
		for(int y = 0; y < 10; y++) {
			vector_add(row, &tmp);
		}
		vector_add(map, row);
		free(row);
	}

	printf("%d\n", *(int *)vector_get(vector_get(map, 9), 1));
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
	int b = 5;
	for(int i = 0; i < 10; i++) {
		int a = 23;
		vector_add(vec, &a);
	}
	vector_add(vec, &b);
	vector_add(vec, &b);
	vector_remove(vec, &b);
	vector_remove(vec, &b);
	vector_add(vec, &b);
	vector_print(vec);
	vector_free(vec);
	vector2d_free(map);
}
