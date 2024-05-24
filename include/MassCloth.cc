#include <cmath>
#include <GL/glut.h>

#include "MassCloth.h"


namespace rvi
{

MassCloth::~MassCloth()
{
	for (auto node : nodes) delete node;
	for (auto spring: springs) delete spring;
}

void MassCloth::Initialize()
{
	nodes.resize(size_x * size_y);

	const auto coeff = M_PI * 5.5f / 6.f;

	// 노드 생성
	for (auto x = 0; x < size_x; ++x) {
	for (auto y = 0; y < size_y; ++y) {
	for (auto z = 0; z < size_z; ++z) {
		const auto nx = x * dx;
		const auto ny = sin(coeff) * y * dy;
		const auto nz = cos(coeff) * y * dy + 30.f;

		auto* node = new Node(Vec3(nx, ny, nz));

		if (x == 0) node->is_fixed = true;

		nodes[x + y * size_y] = node;
	}}}

	// Structural Spring 생성 (Vertical, Horizontal)
	for (auto x = 0; x < size_x; ++x) {
	for (auto y = 0; y < size_y; ++y) {

		if (x < size_x - 1)
			springs.push_back(new MassSpring(node_at(x, y), node_at(x + 1, y), structural_coef));
		if (y < size_y - 1)
			springs.push_back(new MassSpring(node_at(x, y), node_at(x, y + 1), structural_coef));
	}}

	// Shear Spring 생성 (Diagonal)
	for (auto x = 0; x < size_x - 1; ++x) {
	for (auto y = 0; y < size_y - 1; ++y) {
		springs.push_back(new MassSpring(node_at(x, y), node_at(x + 1, y + 1), shear_coef));
		springs.push_back(new MassSpring(node_at(x, y + 1), node_at(x + 1, y), shear_coef));
	}}

	// Bending Spring 생성 (Vertical, Horizontal)
	for (auto x = 0; x < size_x; ++x) {
	for (auto y = 0; y < size_y; ++y) {
		if (x < size_x - 2)
			springs.push_back(new MassSpring(node_at(x, y), node_at(x + 2, y), bending_coef));
		if (y < size_y - 2)
			springs.push_back(new MassSpring(node_at(x, y), node_at(x, y + 2), bending_coef));
	}}

	// Face 생성
	for (auto x = 0; x < size_x - 1; ++x) {
	for (auto y = 0; y < size_y - 1; ++y) {
		faces.push_back(new Node*[3]{node_at(x, y), node_at(x + 1, y + 1), node_at(x, y + 1)});
		faces.push_back(new Node*[3]{node_at(x, y), node_at(x + 1, y), node_at(x + 1, y + 1)});
	}}

	// Face Normal 계산
	for (auto* f: faces)
	{
		const auto& p1 = f[0]->position;
		const auto& p2 = f[1]->position;
		const auto& p3 = f[2]->position;

		face_normals.push_back((p2 - p1).cross(p3 - p1).normalized());
	}

	// Vertex Normal 계산
	static auto vi_at = [this](int x, int y) { return 2 * (x + y * size_y); };

	for (auto x = 0; x < size_x - 1; ++x) {
	for (auto y = 0; y < size_y - 1; ++y) {

		Vec3 tn(0.f, 0.f, 0.f); // temporary normal
		size_t count = 0;
		// 인접한 face가 6개

		const size_t idx[6]
		{
			vi_at(x  , y  ),
			vi_at(x  , y  ) + 1,
			vi_at(x+1, y  ),
			vi_at(x+1, y  ) + 1,
			vi_at(x  , y+1),
			vi_at(x  , y+1) + 1
		};

		for (auto i = 0; i < 6; ++i)
		{
			if (!(idx[i] < face_normals.size()))
				continue;
			
			tn += face_normals[idx[i]];
			++count;
		}

		if (count == 0)
			continue;

		node_at(x, y)->normal = (tn / count).normalized();
	}}
}

void MassCloth::ComputeNormals()
{
	// UNKNOWN 위에서 다 한건데??
}

void MassCloth::AddForce(const Vec3& f)
{
	for (auto node: nodes)
		node->AddForce(f);
}

void MassCloth::ComputeForce(const Vec3& gravity, double dt)
{
	for (auto* node: nodes)
		node->AddForce(gravity * node->mass);
	for (auto* spring: springs)
		spring->InternalForce(dt);
}

void MassCloth::CollisionResponse(const Vec3& ground)
{
	// Ground와 Collision Check
	// TODO Ground에 대한 좀 더 일반적 정의 구현
	for (auto* node: nodes)
	{
		const auto ground_normal = Vec3(0.f, 1.f, 0.f);

		// TODO AddForce 이용하는게 맞지 않나

		if ((node->position - ground).dot(ground_normal) < 0.f && ground_normal.dot(node->velocity) < 0.f)
		{
			const auto normal_vel = ground_normal.dot(node->velocity) * ground_normal;
			const auto tan_vel = node->velocity - normal_vel;

			node->velocity = tan_vel - 0.5f * normal_vel;
		}
	}
}

Node * MassCloth::node_at(int x, int y) const
{
	return nodes[x + y * size_y];
}

};