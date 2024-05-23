#include "Vec2.h"
#include "Vec3.h"

#include <iostream>

using namespace std;
using namespace rvi;

int main()
{
	Vec2 v1(0.f, 1.f);
	Vec2 v2(1.f, 0.f);
	
	cout << (v1 + v2).to_string() << endl;
	cout << (2 * v1).to_string() << endl;

	return 0;
}