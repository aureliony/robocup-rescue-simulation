#pragma once

static constexpr int COLLECT_DURATION = 41, DEPOSIT_DURATION = 41;
static constexpr int FRONT_NEAR = 10, LEFT_NEAR = 5, RIGHT_NEAR = 5;
static constexpr int FRONT_MOVE_BACK = 12;

static constexpr int INF = 0x3f3f3f3f;
static constexpr int WIDTH = 360, HEIGHT = 270, V = WIDTH*HEIGHT;
static constexpr int TARGETDIST = 10, RANDPTTARGETDIST = 5;
static constexpr int INFOLOSTTARGETDIST = 28, SWAMPTARGETDIST = 15, SUPEROBJTARGETDIST = 30;

static constexpr int NUMRANDPTS = 4, RANDNODEMINDIST = 40, CHOOSERANDNODETIMEOUT = 60;

static constexpr int RUSHDEPO = 15, RUSHDEPOSUPERDEPO = 26;

static int depoPhase=1,superObjPhase=1;
static int DestinationX,DestinationY;

static int source,target;
static deque<int> path;

#include "basicVariables.hpp"
#include "mapData.hpp"
#include "aStar.hpp" //conv(x,y)
#include "Place.hpp"
#include "basic.hpp"

static const int depoZones[]={conv(17,252),conv(179,134),conv(342,18)};//CHANGE THIS


static inline void w2Start()
{
	// pcg32_srandom(__rdtsc(), time(NULL)^(intptr_t)&printf);
	rng.seed(__rdtsc());
	resetLoadedObjs();
	resetPhases();
	resetTimeouts();
	InputColourInfo();
	startingw2=false;
}

static void goToSuper()
{
	going_to_place = false;
	going_to_rand_pt = false;
	source = conv(PositionX1,PositionY1);
	target = conv(SuperX,SuperY);
	aStar(source, target);
	double distance = pythag(SuperX - colorSensorX, SuperY - colorSensorY);
	if(distance>SUPEROBJTARGETDIST)
	{
		int i=0;
		while( isWithinCoord(convFinalX(path[i]),convFinalY(path[i]),TARGETDIST) && path[i]!=target )
			i++;
		DestinationX = convFinalX(path[i]);
		DestinationY = convFinalY(path[i]);
	}
	else
	{
		DestinationX = SuperX;
		DestinationY = SuperY;
	}
	trigoSuper(DestinationX, DestinationY);
}
static void goToDepo()
{
	if(depoPhase==1)
	{
		source=conv(PositionX1,PositionY1);
		int tempDist=INT_MAX;
		//choose target depo
		for(const auto& i : depoZones)
		{
			double totalCost=aStar(source, i);
			if(totalCost<tempDist)
			{
				target=i;
				tempDist=totalCost;
			}
		}
		depoPhase=2;
	}

	source = conv(PositionX1,PositionY1);
	aStar(source, target);
	int i=0;
	while( isWithinCoord(convFinalX(path[i]),convFinalY(path[i]),TARGETDIST) && path[i]!=target )
		i++;
	DestinationX = convFinalX(path[i]);
	DestinationY = convFinalY(path[i]);
	trigo(DestinationX, DestinationY);
}

static int placeToGoTo;

static void goToRandPt(uintf8 option)
{
	static int prevNum, currNum, randNode;
	static int randPtTimeout;

	// cout<<"randPtTimeout="<<randPtTimeout<<endl;

	if(option==1)
	{
		currLocIt->objScore -= prevNum - currNum;
		prevNum = currNum;
		printf("\nid = %d, objScore = %d\n\n", currLocIt->id, currLocIt->objScore);

		unsigned int mycol = currLocIt->color;
		if ( LoadedObjects>=6 || (R<=mycol&&mycol<=B&&loaded_objects[mycol]>=2) || (RG<=mycol&&mycol<=GB&&loaded_objects[mycol]>=4))
		{
			going_to_place = false;
			going_to_rand_pt = false;
		}
		return;
	}

	if(!going_to_rand_pt) //initialise
	{
		prevNum = NUMRANDPTS;
		currNum = NUMRANDPTS;
		unsigned int cnt = 0;
		do {
			randNode = currLocIt->loc[randint(0, currLocIt->len - 1)];
			cnt++;
		} while( cnt<=CHOOSERANDNODETIMEOUT && isWithinCoord(convFinalX(randNode),convFinalY(randNode),RANDNODEMINDIST) );

		randPtTimeout = 0;
		going_to_rand_pt = true;
	}

	source = conv(PositionX1, PositionY1);
	target = randNode;
	aStar(source, target);
	int i = 0;
	while( isWithinCoord(convFinalX(path[i]), convFinalY(path[i]), RANDPTTARGETDIST) && path[i]!=target )
		i++;
	DestinationX = convFinalX(path[i]);
	DestinationY = convFinalY(path[i]);

	trigoSweep(DestinationX, DestinationY);
	randPtTimeout++;
	printf("currNum = %d\n", currNum);


	if ( isWithinCoord(convFinalX(randNode), convFinalY(randNode), RANDPTTARGETDIST) ||
		(isInfoLost()&&isWithinCoord(convFinalX(randNode), convFinalY(randNode), INFOLOSTTARGETDIST)) ||
		(isOnSwamp()&&isWithinCoord(convFinalX(randNode), convFinalY(randNode), SWAMPTARGETDIST)) ||
		randPtTimeout>80)
	{
		currNum--;
		randPtTimeout = 0;
		if(currNum==0)
		{
			currLocIt->objScore -= prevNum-currNum;//maybe NUMRANDPTS
			printf("\nid = %d , objScore = %d\n\n", currLocIt->id, currLocIt->objScore);
			going_to_rand_pt = false;
			return;
		}

		unsigned int cnt = 0;
		do {
			randNode = currLocIt->loc[randint(0, currLocIt->len - 1)];
			cnt++;
		} while( cnt<=CHOOSERANDNODETIMEOUT && isWithinCoord(convFinalX(randNode),convFinalY(randNode),RANDNODEMINDIST) );
		randPtTimeout = 0;
	}

	// printf("randNode = %d\n", randNode);

}

static void goToPlace()
{
	source = conv(PositionX1,PositionY1);
	target = placeToGoTo;
	aStar(source, target);
	int i = 0;
	while( isWithinCoord(convFinalX(path[i]),convFinalY(path[i]),TARGETDIST) && path[i]!=target )
		i++;
	DestinationX = convFinalX(path[i]);
	DestinationY = convFinalY(path[i]);

	trigo(DestinationX, DestinationY);

	if( isWithinCoord(convFinalX(target),convFinalY(target),TARGETDIST) ||
		(isInfoLost()&&isWithinCoord(convFinalX(target),convFinalY(target),INFOLOSTTARGETDIST)) || (isOnSwamp()&&isWithinCoord(convFinalX(target),convFinalY(target),SWAMPTARGETDIST)) )
	{
		going_to_place = false;
		going_to_rand_pt = false;
		goToRandPt(0);
	}

}

static inline void navigate()
{
	if(going_to_rand_pt)
	{
		goToRandPt(0);
		return;
	}

	if(going_to_place)
	{
		unsigned int mycol = currLocIt->color;
		if ( (R<=mycol&&mycol<=B&&loaded_objects[mycol]>=2) ||
			(RG<=mycol&&mycol<=GB&&loaded_objects[mycol]>=4) ||
			 (mycol==RGB&&loaded_objects[mycol]>=6) )
		{
			going_to_place = false;
			going_to_rand_pt = false;
		}
		else
		{
			goToPlace();
			return;
		}
	}

	//generate new place and initialise global variables
	currLocIt = navi.getBest();
	placeToGoTo = currLocIt->loc[randint(0, currLocIt->len - 1)];
	going_to_place = true;
	going_to_rand_pt = false;
	goToPlace();
}
