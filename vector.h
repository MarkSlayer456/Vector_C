#ifndef VECTOR_H_
#define VECTOR_H_
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct vector {
	int count;
	size_t item_size;
	int capacity;
	void *values;
} Vector;

Vector *vector_new(size_t size) {
	int default_length = 2;
	Vector *vector = calloc(1, sizeof(Vector));
	vector->capacity = default_length;
	vector->count = 0;
	vector->item_size = size;
	vector->values = calloc(default_length, vector->item_size);
	return vector;
}

void *vector_get(Vector *vec, int index) {
	return (unsigned char *)vec->values+(index*vec->item_size);
}

int vector_add(Vector *vec, void *item) {
	if(vec->count+1 >= vec->capacity) {
		vec->capacity *= 2;
		printf("vector new cap: %d\n", vec->capacity);
		vec->values = realloc(vec->values, vec->capacity*vec->item_size);
	}
	memcpy((unsigned char *)vec->values+(vec->count*vec->item_size), item, vec->item_size);
	vec->count++;
}

// removes first occurance of *item stored in *vec
void vector_remove(Vector *vec, void *item) {
	for(int i = 0; i < vec->count; i++) {
		if(memcmp(vector_get(vec, i), item, vec->item_size) == 0) {
			for(int j = i; j < vec->count-1; j++) {
				memcpy(vector_get(vec, j), vector_get(vec, j+1), vec->item_size);
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
				memcpy(vector_get(vec, j), vector_get(vec, j+1), vec->item_size);
			}
			vec->count--;
			break;
		}
	}
}

void *vector_get2d(Vector *vec, int x, int y) {
	Vector *vecy = *(Vector **) vector_get(vec, x);
	unsigned char *data = (unsigned char *) vector_get(vecy, y);
	return data;
}

void *vector_get3d(Vector *vec, int x, int y, int z) {
	Vector *vecy = *(Vector **) vector_get(vec, x);
	Vector *vecz = *(Vector **) vector_get(vecy, y);
	unsigned char *data = (unsigned char *) vector_get(vecz, z);
	return data;
}

void vector_replace(Vector *vec, int index, void *value) {
	unsigned char *data = (unsigned char *) vec->values;
	memcpy(data+(index*vec->item_size), value, vec->item_size);
}

void vector_replace2d(Vector *vec, int x, int y, void *value) {
	Vector *row = *(Vector **)vector_get(vec, x);
	unsigned char *data = (unsigned char *) row->values;
	memcpy(data+(y*row->item_size), value, row->item_size);
}

void vector_replace3d(Vector *vec, int x, int y, int z, void *value) {
	Vector *row = *(Vector **)vector_get(vec, x);
	Vector *col = *(Vector **)vector_get(row, y);
	unsigned char *data = (unsigned char *) col->values;
	memcpy(data+(z*row->item_size), value, row->item_size);
}

void vector_free(Vector *vec) {
	free(vec->values);
	free(vec);
}

void vector2d_free(Vector *vec) {
	Vector **rows = (Vector **)vec->values;

	for(int i = 0; i < vec->count; i++) {
		Vector *row = rows[i];
		free(row->values);
		free(row);
	}
	free(vec->values);
	free(vec);
}

void vector3d_free(Vector *vec) {
	Vector **rows = (Vector **)vec->values;

	for(int i = 0; i < vec->count; i++) {
		Vector *row = rows[i];
		for(int j = 0; j < row->count; j++) {
			Vector *col = (Vector *)row->values;
			free(col->values);
			free(col);
		}
		free(row->values);
		free(row);
	}
	free(vec->values);
	free(vec);
}
#endif
