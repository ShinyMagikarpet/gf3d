#include "gf3d_shape.h"

float gf3d_line_length(Line line) {
	
	return vector3d_magnitude_between(line.start.p, line.end.p);
}

Box gf3d_box(float x, float y, float z, float w, float h, float d) {

	Box box;
	gf3d_box_set(box, x, y, z, w, h, d);
	return box;
}

Shape gf3d_shape_box(float x, float y, float z, float w, float h, float d) {

}

Shape gf3d_shape_from_box(Box b) {

}
