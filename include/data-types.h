#ifndef DATA_TYPES_H
#define DATA_TYPES_H

typedef struct {
	float x;
	float y;
} point;

typedef struct {
	float x;
	float y;
	float tex_x;
	float tex_y;
} point_tex;

typedef point polygon[3];

typedef point_tex polygon_tex[3];

#endif
