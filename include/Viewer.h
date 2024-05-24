#pragma once

#include "Simulator.h"

namespace rvi
{

class Viewer
{
public:
	Simulator simulator;

public:
	Viewer() = default;
	~Viewer() = default;

public:
	void Initialize();
	void Render();
	void Reshape(int w, int h);
	void Mouse(int mouse_event, int state, int x, int y);
	void Motion(int x, int y);
	void Keyboard(unsigned char key, int x, int y);
	void Update();

private:
	float zoom_ = 120.f;
	// TODO: use Vec2
	float rotate_[2] = { 0.f, 0.f };
	float translate_[2] = { 0.f, 0.f };
	float mouse_coord_[2] = { 0.f, 0.f };
	float mouse_event_[2] = { 0.f, 0.f };
	bool start_ = false;
	int render_mode_;
	bool interaction_mode_ = false;

};

}; // namespace rvi