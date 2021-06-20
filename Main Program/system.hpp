#pragma once
#define _USE_MATH_DEFINES

// #include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <cassert>
#include <ctime>
#include <vector>
#include <set>
#include <deque>
#include <queue>
#include <intrin.h> //for __rdtsc() to seed the prng
#define PI M_PI
typedef int_fast8_t intf8;
typedef uint_fast8_t uintf8;
using namespace std;
#include "myRandint.hpp"
#define pass ()0
#define DLL_EXPORT extern __declspec(dllexport)

char AI_MyID[2] = {'1','6'};//The robot ID : It must be two char, such as '00','kl' or 'Cr'.
static int Duration = 0, SuperDuration = 0, CurAction = -1;
static int SuperObj_Num = 0, CurGame = 0;
static int SuperObj_X = 0, SuperObj_Y = 0;
static int Teleport = 0, LoadedObjects = 0;
static int US_Front = 0, US_Left = 0, US_Right = 0;
static int CSLeft_R = 0, CSLeft_G = 0, CSLeft_B = 0, CSRight_R = 0, CSRight_G = 0, CSRight_B = 0;
static int PositionX = 0, PositionY = 0;
static int Compass = 0, Time = 0;
static int TM_State = 0, LED_1 = 0, AI_SensorNum = 13;
static int WheelLeft = 0, WheelRight = 0, MyState = 0;

static void Game0();
static void Game1();//func prototypes

extern "C"{
DLL_EXPORT void SetGameID(int GameID){CurGame = GameID;}
DLL_EXPORT int GetGameID(){return CurGame;}
DLL_EXPORT char* GetTeamName(){return (char*)"NYCasuals";}
DLL_EXPORT int GetCurAction(){return CurAction;}
DLL_EXPORT int GetTeleport(){return Teleport;}
DLL_EXPORT void SetSuperObj(int X, int Y, int num){SuperObj_X = X;SuperObj_Y = Y;SuperObj_Num = num;}
DLL_EXPORT void GetSuperObj(int *X, int *Y, int *num){*X = SuperObj_X;*Y = SuperObj_Y;*num = SuperObj_Num;}
DLL_EXPORT void SetDataAI(volatile int* packet, volatile int *AI_IN){int sum = 0;US_Front = AI_IN[0]; packet[0] = US_Front; sum += US_Front;US_Left = AI_IN[1]; packet[1] = US_Left; sum += US_Left;US_Right = AI_IN[2]; packet[2] = US_Right; sum += US_Right;CSLeft_R = AI_IN[3]; packet[3] = CSLeft_R; sum += CSLeft_R;CSLeft_G = AI_IN[4]; packet[4] = CSLeft_G; sum += CSLeft_G;CSLeft_B = AI_IN[5]; packet[5] = CSLeft_B; sum += CSLeft_B;CSRight_R = AI_IN[6]; packet[6] = CSRight_R; sum += CSRight_R;CSRight_G = AI_IN[7]; packet[7] = CSRight_G; sum += CSRight_G;CSRight_B = AI_IN[8]; packet[8] = CSRight_B; sum += CSRight_B;PositionX = AI_IN[9]; packet[9] = PositionX; sum += PositionX;PositionY = AI_IN[10]; packet[10] = PositionY; sum += PositionY;TM_State = AI_IN[11]; packet[11] = TM_State; sum += TM_State;Compass = AI_IN[12]; packet[12] = Compass; sum += Compass;Time = AI_IN[13]; packet[13] = Time; sum += Time;packet[14] = sum;}
DLL_EXPORT void GetCommand(int *AI_OUT){AI_OUT[0] = WheelLeft;AI_OUT[1] = WheelRight;AI_OUT[2] = LED_1;AI_OUT[3] = MyState;}

DLL_EXPORT void OnTimer()
{
	if(CurGame==0) Game0();
	else Game1();
}

}//extern "C"