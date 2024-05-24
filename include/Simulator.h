#pragma once

#include "Vec3.h"

namespace rvi
{

class MassCloth; 
class Cylinder;

struct LightInfo
{
	float position[4]     = { 150.f, 150.f, 0.f, 1.f };
	float direction[4]    = { -1.f, -1.f, 0.f, 0.f };
	float ambient[4]      = { 0.3f, 0.3f, 0.3f, 1.f };
	float diffuse[4]      = { 0.8f, 0.8f, 0.8f, 1.0f };
	float specular[4]     = { 1.0f, 1.0f, 1.0f, 1.0f};
	float front_color[4]  = { 0.8f, 0.8f, 0.8f, 1.f };
	float mat_shininess   =   20.f;
	float no_mat[4]       = { 0.f, 0.f, 0.f, 1.f };
	float mat_specular[4] = { 1.f, 1.f, 1.f, 1.f};
};

class Simulator
{
public:
	Simulator() = default;
	~Simulator() = default;

public:
	void Initialize();
	void Update();
	void Render();
	void Lighting();
	void DrawGround();

private:
	MassCloth* cloth_;
	Cylinder* cylinder_;
	Vec3 ground_;
	float timestamp_;
	LightInfo li_;
};


}; // namespace rvi