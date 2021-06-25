#include <iostream>
#include <cstdio>
#include <cmath>
#include <limits>
#include <cassert>
#include <chrono>
#include <set>
#include <queue>
typedef int_fast8_t intf8;
typedef uint_fast8_t uintf8;
using namespace std;

static const int INF = 0x3f3f3f3f;
static const int WIDTH = 360, HEIGHT = 270, V = WIDTH*HEIGHT;
#include "mapData.hpp" //uint8_t w2map[]
// int path[V];
deque<unsigned int> path;
int LoadedObjects = 1;
#include "aStar.hpp"

int main()
{
	// for (int i=0;i<=359;i++)
	// {
	// 	Compass = i;
	// 	printf("%d\t%d\n",Compass,getCompassRelPos());
	// }
	// return 0;

	int src = con(158,44), target = con(209,203);

	aStar(src,target);

	for(const auto& i : path)
	{
		printf("(%d,%d)\n",conX(i),conY(i));
		// printf("(%d,%d)\n",convX(path[i]),convY(path[i]));
	}
}