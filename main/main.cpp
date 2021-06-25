#include "system.hpp"
using namespace std;
static constexpr bool ENABLEDEBUG=false;
#undef printf
#undef assert
#define printf(...) (void)0 //disable printf
#define assert(...) (void)0 //disable asserts
#include "navigation.hpp"
// static void Game0(){return;}
#include "world1.hpp"
#include "predictXY.hpp"


static void Game1() {
	// if(isInsideTrap()&&LoadedObjects>0)
	// {
	// 		speed(0,0);
	//   	return;
	// }
	/*enable for debug purposes only*/

	// system("cls");

	if(startingw2) w2Start();

	if(SuperObj_X>0&&SuperObj_Y>0&&!going_to_super&&SuperObj_X!=SuperX&&SuperObj_Y!=SuperY)
	{
		SuperX = SuperObj_X;
		SuperY = SuperObj_Y;
		going_to_super = true;
	}

	static int prevCompass=0;
	if(!isInfoLost())
	{
		PositionX1 = PositionX;
		PositionY1 = PositionY;
	}
	else if (PositionX1!=-1&&PositionY1!=-1) //do not execute if teleport spawns inside info-lost zone
	{
		Vector2 bot;
		bot.setWheels(WheelLeft, WheelRight);
		pair <double, double> position;
		position = bot.rotate(PositionX1, PositionY1, prevCompass, Compass, isOnSwamp() ? 12 : 60);
		// int i = min(2, (int)path.size());
		// PositionX1=convFinalX(path[i]);
		// PositionY1=convFinalY(path[i]);
		PositionX1=(int)round(position.first);
		PositionY1=(int)round(position.second);
	}
	prevCompass=Compass;

	colorSensorX = PositionX1+(int)round(cos((Compass+90.0)*PI/180)*5);
	colorSensorY = PositionY1+(int)round(sin((Compass+90.0)*PI/180)*5);

	if(exitingDepo)
	{
		if(isOnDeposit())
		{
			speed(-5,-5);
			return;
		}
		else
		{
			speed(5,5);
			exitingDepo=false;
			return;
		}
	}
	if(depositing) //this fixes the penalty while depositing issue
	{
		if(Duration==0)
		{
			resetLoadedObjs();
			resetPhases();
			SuperX = 0;
			SuperY = 0;
			// tempLoc = -1;
			depositing=false;
			// exitingDepo=true;
			// return;
			/*enable these to exit depo*/
		}
		else if(!isOnDeposit())
		{
			resetPhases();
			Duration=0;
			depositing=false;
		}
	}

	if(going_to_super) SuperObjTimeout++;
	if(SuperObjTimeout>330)
	{
		resetPhases();
		going_to_super=false;
		SuperObjTimeout=0;
	}
	if(WallTimeout>30||TrapTimeout>30)
	{
		resetPhases();
		WallTimeout=0;
		TrapTimeout=0;
	}
	if(isInsideTrap()&&LoadedObjects>0)
	{
		LED_1=0;
		resetLoadedObjs();
		resetPhases();
		// tempLoc=-1;
		going_to_place=false;
		going_to_rand_pt=false;
		cout << "\nENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n";
		cout << "ENTERED TRAP\n\n";
	}

	if(Duration>0) {Duration--;return;}
	else if(Duration==0) LED_1=0;
	else /*Duration<0*/ Duration=0;

	if (isOnRed() && posIsInColorLoc(PositionX1, PositionY1) && loaded_objects[R]<2 && ( (LoadedObjects<6&&!going_to_super) || (LoadedObjects<5&&going_to_super) ) && !isRushing()) find_obj(R);
	else if (isOnGreen() && posIsInColorLoc(PositionX1, PositionY1) && loaded_objects[G]<2 && ( (LoadedObjects<6&&!going_to_super) || (LoadedObjects<5&&going_to_super) ) && !isRushing() ) find_obj(G);
	else if (isOnBlack() && blackIsInColorLoc(PositionX1, PositionY1) && posIsInColorLoc(PositionX1, PositionY1) && loaded_objects[B]<2 && ( (LoadedObjects<6&&!going_to_super) || (LoadedObjects<5&&going_to_super) ) && !isRushing() ) find_obj(B);
	else if (isOnSuperObj() && LoadedObjects<6 && going_to_super ) find_obj(S);
	else if (isOnYellow() && LoadedObjects>0) avdYellow();
	// else if (isOnYellow() && LoadedObjects>0) speed(-3,-3);
	// else if (isNearTrapXY() && LoadedObjects>0) avdTrapXY();
	// else if (US_Front<=FRONT_NEAR||US_Left<=LEFT_NEAR||US_Right<=RIGHT_NEAR) avdWallNear();
	else if (US_Front<=FRONT_MOVE_BACK && !going_to_place && !going_to_rand_pt) {
		if(isOnSwamp()) speed(-5,-5);
		else speed(-3,-3);
	}
	else if (US_Left<=6 && !going_to_place && !going_to_rand_pt) speed(5,2);
	else if (US_Right<=6 && !going_to_place && !going_to_rand_pt) speed(2,5);
	else if (isOnDeposit() && LoadedObjects>0 && depoPhase==2) deposit();
	// else if (isOutOfXY()>0&&!isInfoLost()) avdNSEW(); //not needed if robot guaranteed wont go out
	else if (LoadedObjects<6 && going_to_super) goToSuper();
	else if (LoadedObjects>=6 || shouldRush()) goToDepo();
	else if (LoadedObjects<6)
	{
		navigate();
		if (US_Front<=FRONT_MOVE_BACK) {
			if(isOnSwamp()) speed(-5,-5);
			else speed(-3,-3);
		}
		else if (US_Left<=6) speed(5,2);
		else if (US_Right<=6) speed(2,5);
	}

	cout << source << " " << target << endl;

	// int reversedwheels;
	// WheelLeft*=-1;
	// WheelRight*=-1;
	// swap(WheelLeft,WheelRight);

	// for(int i=0;i<N;i++)
 //    {
 //        // printf("path[%d] = (%d,%d)\n",i,convX(path[i]),convY(path[i]));
 //        printf("(%d,%d)\n",convX(path[i]),convY(path[i]));
 //        if(path[i]==target) break;
 //    }
	// printf("\n");

}


extern "C" {
	DLL_EXPORT char* GetDebugInfo()
	{
		if(!ENABLEDEBUG) return (char*)(0);
		static char info[1024];
		sprintf(info,"going_to_place=%d;going_to_rand_pt=%d;going_to_super=%d;rDist[3]=%d;currLocIt->color=%d;SuperObjTimeout=%d;WallTimeout=%d;TrapTimeout=%d;loaded_objects[S]=%d;loaded_objects[R]=%d	;loaded_objects[G]=%d;loaded_objects[B]=%d;loaded_objects[RG]=%d;loaded_objects[RB]=%d;loaded_objects[GB]=%d;loaded_objects[RGB]=%d;WheelLeft=%d;WheelRight=%d;PositionX1=%d;PositionY1=%d;",	going_to_place,going_to_rand_pt,going_to_super,rDist[3],currLocIt->color,SuperObjTimeout,WallTimeout,TrapTimeout,loaded_objects[S],loaded_objects[R],loaded_objects[G],loaded_objects[B],loaded_objects[	RG],loaded_objects[RB],loaded_objects[GB],loaded_objects[RGB],WheelLeft,WheelRight,PositionX1,PositionY1);
		return info;
	}
}