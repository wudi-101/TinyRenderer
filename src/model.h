#ifndef MODEL_H
#define MODEL_H

#include "geometry.h"
#include <vector>

class Model {
private:
	std::vector<Vec3f> verts_;
	std::vector<std::vector<int>> faces_;

public:
	Model(const char* filename);
	~Model();
	int nverts();
	int nfaces();
	Vec3f vert(int i);
	std::vector<int> face(int idx);
};

#endif // !MODEL_H
