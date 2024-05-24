#pragma once

#include <vector>
#include "Vec3.h"

namespace rvi
{

struct Node;
struct MassSpring;

class MassCloth
{
public:
	MassCloth() = default;
	~MassCloth();

public:
	void Initialize();
	void ComputeNormals();
	void ComputeForces(const Vec3& gravity, double dt);
	void Integrate(double dt);
	void CollisionResponse(const Vec3& ground);

	Node* node_at(int x, int y) const;
	void draw() const;

private:


private:
	std::vector<Node*> nodes;
	std::vector<MassSpring*> springs;
	std::vector<Node**> faces;
	std::vector<Vec3> face_normals;
	std::vector<Vec3> vertex_normals;


	// TODO
	void CollisionResponse();

	int size_x, size_y, size_z;
	double dx, dy, dz;
	double structural_coef, shear_coef, bending_coef;

	int n_iteration;
	int draw_mode;
};

}; // namespace rvi