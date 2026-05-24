#ifndef VECTOR_H_
#define VECTOR_H_
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct vector {
	int count;
	size_t item_size;
	int capacity; 
	void **values;
} Vector;

Vector *vector_new(size_t size) {
	int default_length = 2;
	Vector *vector = calloc(1, sizeof(Vector));
	vector->capacity = default_length;
	vector->count = 0;
	vector->item_size = size;
	vector->values = calloc(default_length, sizeof(void *));
	for(int i = 0; i < default_length; i++) {
		vector->values[i] = calloc(1, vector->item_size);
	}
	return vector;
}

int vector_add(Vector *vec, void *item) {
	if(vec->count+1 >= vec->capacity) {
		vec->capacity *= 2;
		vec->values = realloc(vec->values, vec->capacity*sizeof(void *));
		for(int i = vec->count; i < vec->capacity; i++) {
			vec->values[i] = calloc(1, vec->item_size);
		}
	}
	memcpy(vec->values[vec->count++], item, vec->item_size);
}

// removes first occurance of *item stored in *vec
void vector_remove(Vector *vec, void *item) {
	for(int i = 0; i < vec->count; i++) {
		if(memcmp(vec->values[i], item, vec->item_size) == 0) {
			for(int j = i; j < vec->count-1; j++) {
				vec->values[j] = vec->values[j+1];
			}
			vec->count--;
			break;
		}
	}
}

void vector_remove_index(Vector *vec, int index) {
	for(int i = 0; i < vec->count; i++) {
		if(i == index) {
			for(int j = i; j < vec->count-1; j++) {
				vec->values[j] = vec->values[j+1];
			}
			vec->count--;
			break;
		}
	}
}

void *vector_get(Vector *vec, int index) {
	return vec->values[index];
}

void *vector_get2d(Vector *vec, int x, int y) {
	return vector_get(vector_get(vec, x), y);
}

void *vector_get3d(Vector *vec, int x, int y, int z) {
	return vector_get(vector_get(vector_get(vec, x), y), z);
}

void vector_replace(Vector *vec, int index, void *value) {
	for(int i = 0; i < vec->count; i++) {
		if(i == index) {
			memcpy(vec->values[i], value, vec->item_size);
		}
	}
}

void vector_replace2d(Vector *vec, int x, int y, void *value) {
	for(int i = 0; i < vec->count; i++) {
		Vector *vecy = (Vector *)vector_get(vec, i);
		for(int j = 0; j < vecy->count; j++) {
			if(i == x && j == y) {
				memcpy(vector_get2d(vec, x, y), value, vec->item_size);
			}
		}
	}
}

void vector_replace3d(Vector *vec, int x, int y, int z, void *value) {
	for(int i = 0; i < vec->count; i++) {
		Vector *vecy = (Vector *)vector_get(vec, i);
		for(int j = 0; j < vecy->count; j++) {
			Vector *vecz = (Vector *)vector_get(vecy, j);
			for(int k = 0; k < vecy->count; k++) {
				if(i == x && j == y && k == z) {
					memcpy(vector_get3d(vecz, x, y, z), value, vec->item_size);
				}
			}
		}
	}
}
#endif
