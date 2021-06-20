#pragma once

enum {S,R,G,B,RG,RB,GB,RGB,TOTAL_OBJ_COLOURS};
map<int,string> intToStr={
	{R,"R"},
	{G,"G"},
	{B,"B"}
};
map<string,int> strToInt={
	{"R",R},
	{"G",G},
	{"B",B},
	{"RG",RG},
	{"RB",RB},
	{"GB",GB},
	{"RGB",RGB}
};
static unsigned int loaded_objects[TOTAL_OBJ_COLOURS] = {0};
static bool startingw2=true;
static bool depositing=false;
static bool exitingDepo=false;
static int minSpeed=5,maxSpeed=5;
static int theta=-1,AngleDiff,CWAngleDiff,ACWAngleDiff;
static int PositionX1=-1,PositionY1=-1,colorSensorX=-1,colorSensorY=-1;
static int SuperX=0,SuperY=0;
static bool going_to_super=false,going_to_place=false,going_to_rand_pt=false;
static int SuperObjTimeout=0,TrapTimeout=0,WallTimeout=0;