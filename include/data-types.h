#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#define a_free(p) { free(p); p = NULL; }

#define POINT(p) 

// TODO: Implement POINT_LIST typecast macro which takes a float array and
// returns a pointlist.

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

point_tex* point_tex_list_new(int point_count);

#endif
