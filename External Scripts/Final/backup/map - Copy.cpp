#include <iostream>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <chrono>
#include <queue>
#include <set>
using namespace std;

static const int INF = 0x3f3f3f3f;
static const int WIDTH = 360, HEIGHT = 270, V = WIDTH*HEIGHT;
#include "mapData.hpp" //uint8_t w2map[]
// int path[V];
deque<int> path;
int Compass=270;
#include "aStar.hpp"

int main()
{
	int src = con(12,15), target = con(232,252);

	aStar(src,target);

	for(int i=0, n=path.size(); i<n; i++)
    {
        printf("(%d,%d)\n",conX(path[i]),conY(path[i]));
        // printf("(%d,%d)\n",convX(path[i]),convY(path[i]));
        // if(path[i]==target) break;
    }
}