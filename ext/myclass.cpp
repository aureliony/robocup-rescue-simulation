#include <bits/stdc++.h>
#include <intrin.h>
using namespace std;
#include "myRandint.hpp"

#include "mapData.hpp"
#include "colorLocsData.hpp"
static int Compass=0;
static const int INF = 0x3f3f3f3f;
static const int WIDTH = 360, HEIGHT = 270, V = WIDTH*HEIGHT;
static deque<int> path;
static int LoadedObjects=1;
#include "aStar.hpp"

static inline double PYTHAG(int a,int b){return sqrt(a*a+b*b);}
static inline double PYTHAG(double a,double b){return sqrt(a*a+b*b);}
static int PositionX1,PositionY1;

enum {S,R,G,B,RG,RB,GB,RGB,TOTAL_OBJ_COLOURS};
static unsigned int loaded_objects[TOTAL_OBJ_COLOURS]={0,2,2,0,0,0,0,0};

struct Place {
	const unsigned int id;
	int objScore;
	double dist;
	const unsigned int color;
	const unsigned int midNode;
	const uint32_t *const loc;
	const size_t len;
};

static class {
public:
	vector<Place> places = { //MODIFY THIS
		(Place){0, 0, 0, B, bLoc0[sizeof(bLoc0)/sizeof(bLoc0[0])/2], bLoc0, sizeof(bLoc0)/sizeof(bLoc0[0])},
		(Place){1, 0, 0, B, bLoc1[sizeof(bLoc1)/sizeof(bLoc1[0])/2], bLoc1, sizeof(bLoc1)/sizeof(bLoc1[0])},
		(Place){2, 0, 0, B, bLoc2[sizeof(bLoc2)/sizeof(bLoc2[0])/2], bLoc2, sizeof(bLoc2)/sizeof(bLoc2[0])},
		(Place){3, 0, 0, B, bLoc3[sizeof(bLoc3)/sizeof(bLoc3[0])/2], bLoc3, sizeof(bLoc3)/sizeof(bLoc3[0])},
		(Place){4, 0, 0, G, gLoc0[sizeof(gLoc0)/sizeof(gLoc0[0])/2], gLoc0, sizeof(gLoc0)/sizeof(gLoc0[0])},
		(Place){5, 0, 0, G, gLoc1[sizeof(gLoc1)/sizeof(gLoc1[0])/2], gLoc1, sizeof(gLoc1)/sizeof(gLoc1[0])},
		(Place){6, 0, 0, R, rLoc0[sizeof(rLoc0)/sizeof(rLoc0[0])/2], rLoc0, sizeof(rLoc0)/sizeof(rLoc0[0])},
		(Place){7, 0, 0, R, rLoc1[sizeof(rLoc1)/sizeof(rLoc1[0])/2], rLoc1, sizeof(rLoc1)/sizeof(rLoc1[0])}
	};

	void printPlaces(void){
		for(const auto& i : places){
			printf("%d %d %.1f\n", i.id, i.objScore, i.dist);
		}
		cout<<endl;
	}

	struct {
		bool operator()(const Place& p1, const Place& p2){
			unsigned int num1=2,num2=2;
			
			if(R<=p1.color&&p1.color<=B)
				num1 = 2;
			else if (RG<=p1.color&&p1.color<=GB)
				num1 = 4;
			else if(p1.color==RGB)
				num1 = 6;
			else
				cout << "ERROR CHECKING PLACE1 COLOR\n";

			if(R<=p2.color&&p2.color<=B)
				num2 = 2;
			else if (RG<=p2.color&&p2.color<=GB)
				num2 = 4;
			else if(p2.color==RGB)
				num2 = 6;
			else
				cout << "ERROR CHECKING PLACE2 COLOR\n";

			if(loaded_objects[p1.color]>=num1 && loaded_objects[p2.color]<num2)
				return false;//swap
			if(loaded_objects[p1.color]<num1 && loaded_objects[p2.color]>=num2)
				return true;//dont swap
			//fewer visits first, followed by dist from robot
			return p1.objScore==p2.objScore ? p1.dist<p2.dist : p1.objScore>p2.objScore;
		}
	}lessDist;

	void updateDists(void)
	{
		for(auto& i : places) //update distances
			i.dist = aStar(conv(PositionX1, PositionY1), i.midNode);
	}

	vector<Place>::iterator getBest(void){
		updateDists();
		return min_element(places.begin(), places.end(), lessDist);
	}

} navi;

int main()
{
	rng.seed(__rdtsc());
	PositionX1=randint(0,359);PositionY1=randint(0,269);
	cout<<PositionX1<<" "<<PositionY1<<endl;
	cout << navi.getBest()->id <<endl ;
	navi.printPlaces();

}
