#pragma once

//variables go here  MAKE SURE NO OVERLAP WITH OTHER VARIS
static constexpr int W1_COLLECT_DURATION = COLLECT_DURATION;//+6

static bool startingw1=true,robotcolor;

enum {leftt,rightt}TracingSide;

static int FRONT;
static int RIGHT;
static int LEFT;
static int TimeOut = 0;
static int TimeOutNoObj = 0;
static int TOTO = 0;
static int TOTONO = 0;
static int bonusType = RGB;
static int bonusTimeOut = 0;
static int DepoTime = 0;
static int preProgramTimer = 0;

static bool Tracing;
static bool isFindingObj = false;
static bool Bonus = false;
static bool bonusColour[4] = {false};
static int preProgramOn = 0;
static int whichDepo;

static int THRESH = 20;
static int PREV_US[2] = {0};

static constexpr int TIMEOUTNOOBJ = 200;
static constexpr int TIMEOUT = 100;
static constexpr int TIMEOUTNO = 200;
static constexpr int SWEEP = 15;
static constexpr int TELEPORTTIME = 180;

#include "world1functions.hpp"


static void Game0()
{
	if (shouldTp()) { Teleport = 3; return; }

	Tracing = true;

	if (startingw1) startw1();

	static int counter10s=0;
	if(counter10s<=145)
	{
		counter10s++;
	}
	else
	{
		counter10s=0;
		//THRESH = randint(5,15);
	}
	cout<<"counter10s="<<counter10s<<endl;

	//Check if robot should be wall tracing
	checkTracing();

	//Conditions for changing sides (Trying to copy russia)
	//conditions();

	/*
	//Initialize bonus Comment out to disable bonus
	if (isOnBonus1()==3 && !Bonus && bonusTimeOut<300 && (int)loaded_objects[bonusType]<=((int)((bonusType-1)/3)+4)){
		Bonus = true;
	}*/

	//Bonus timeout
	if (Bonus){
		Tracing = false;
		if ( (int)loaded_objects[bonusType]>((int)((bonusType-1)/3)+4)) //(bonusType-1)/3)*2+2) FOR DOUBLE RGB
		{
			Bonus = false;
		}
		bonusTimeOut ++;
		if (bonusTimeOut>=300){
			Bonus = false;
		}
	}


	if(exitingDepo)
	{
		int compTarget;

		if (whichDepo == 1) compTarget = 315;
		else if (whichDepo == 2) compTarget = 45;
		else if (whichDepo == 3) compTarget = 135;
		else compTarget = 225;

		if (DepoTime>8)
		{
			exitingDepo=false;
			DepoTime=0;
			speed(3,-3);setDuration(300);
			printf("ExitDepo\n");
			return;
		}
		if (Compass>compTarget)
		{
			WheelLeft=-3;
			WheelRight=-5;
		}
		else if (Compass<compTarget)
		{
			WheelLeft=-5;
			WheelRight=-3;
		}
		else
		{
			WheelLeft=-5;
			WheelRight=-5;
		}
		DepoTime++;
		return;
		// if(isOnDeposit1())
		// {
		// 	speed(-5,-5);
		// 	return;
		// }
		// else
		// {
		// 	speed(5,5);
		// 	exitingDepo=false;
		// 	return;
		// }
	}

	if(depositing) //this fixes the penalty while depositing issue
	{
		if(Duration==0)
		{
			resetLoadedObjs();
			whichDepo = checkDirection();
			depositing=false;
			exitingDepo=true;
			return;
		}
		else if(!isOnDeposit1())
		{
			Duration=0;
			depositing=false;
		}
	}

	/*if objects dont disappear then enable this*/
	// if(isFindingObj && Duration<6){
	// 	if (US_Front<=5) speed(-4, -1);
	// 	else if (US_Front<11) speed(-2, 3);
	// 	else speed(3, 3);
	// 	if(Duration==0) isFindingObj=false;
	// }
	if(isInsideTrap1()&&LoadedObjects>0)
	{
		LED_1=0;
		resetLoadedObjs();
		// tempLoc=-1;
		cout << "\nENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n\n";
	}

	if(Duration>0)
	{
		Duration--;
		return;
	}
	else if(Duration==0) LED_1=0;
	else Duration=0;

	//All wall trace timeout stuff
	timeouts();

	int TODOAVOIDTRAPTRACING;

	if (isOnRed1() && (shouldCollect(R) || shouldCollectLastMinute()) && LoadedObjects<6) find_obj_world1(R);
	else if (isOnGreen1() && (shouldCollect(G) || shouldCollectLastMinute()) && LoadedObjects<6) find_obj_world1(G);
	else if (isOnBlack1() && (shouldCollect(B) || shouldCollectLastMinute() || isOnBonus1() ) && LoadedObjects<6 ) find_obj_world1(B);
	else if (isOnDeposit1() && (shouldGoDepo() || (Time>TELEPORTTIME-10 && LoadedObjects>0) )) depositw1();
	else if (isOnYellow1() && LoadedObjects>0) avdYellowWorld1();
	else if (isOnFloorDark1() && (Compass<45 || Compass>315) && (US_Front>70 && US_Front<78) && !(shouldGoDepo() || (Time>TELEPORTTIME-10 && LoadedObjects>0)) ) {speed(0,3);setDuration(120);}
	else if (isOnFloorLight1() && (Compass<225 && Compass>135) && !(shouldGoDepo() || (Time>TELEPORTTIME-10 && LoadedObjects>0)) ) {speed(0,3);setDuration(120);}
	else if (isOnFloorDarkUp1() && (15<=US_Front && US_Front<=22) && (Compass<45 || Compass>315) && !(shouldGoDepo() || (Time>TELEPORTTIME-10 && LoadedObjects>0)) ) {speed(0,3);setDuration(120);}
	else if (isOnFloorLightLow1() && (13<=US_Front && US_Front<=20) && (Compass>135 && Compass<225) && !(shouldGoDepo() || (Time>TELEPORTTIME-10 && LoadedObjects>0)) ) {speed(0,3);setDuration(120);}
	else if (isOnDeposit1() && !(shouldGoDepo() || (Time>TELEPORTTIME-10 && LoadedObjects>0)) ) avdDepositWorld1();
	else if (isOnWhite1() && Bonus) avdWhiteWorld1();
	else if (US_Front<=2 && US_Right<=2 && US_Left<=2) avdWallsAll();
	else if ((US_Front<=5 || US_Left<=2 || US_Right<=2) && Tracing) avdWallsTracing();
	else if ((US_Front<=12 || US_Right<=7 || US_Left<=7) && !Tracing) avdWallWorld1();
	//else if (!shouldGoDepo() && TracingSide == rightt) speed(5,2);
	//else if (!shouldGoDepo() && TracingSide == leftt) speed(2,5);
	else if (Tracing) WallTrace();
	else if (LoadedObjects<6) sweep(SWEEP, 2, 4);
	else speed(3, 3);

}
