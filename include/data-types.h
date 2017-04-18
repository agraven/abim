#ifndef DATA_TYPES_H
#define DATA_TYPES_H
#include <stdlib.h>

#define safe_free(p) { free(p); p = NULL; }

typedef struct {
	float x;
	float y;
} Vector;

#endif
