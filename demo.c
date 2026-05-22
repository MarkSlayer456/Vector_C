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
	}

	printf("%d\n", *(int *)vector_get(vector_get(map, 9), 1));

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

}
